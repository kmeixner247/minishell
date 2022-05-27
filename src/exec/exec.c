/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/27 15:59:04 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	try_paths(t_shell *shell, char **args, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i], ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin2(paths[i], "/");
		paths[i] = ft_strjoin2(paths[i], args[0]);
		execve(paths[i], args, envp);
		free(paths[i]);
		i++;
	}
	fprintf(stderr, "Couldn't find command %s\n", args[0]);
	free(paths);
}

void	children(t_shell *shell, t_token *token)
{
	char	**args;
	char	**envp;

	handle_redirs_single(shell, token);
	envp = get_env(shell->env);
	dup2(token->infd, 0);
	dup2(token->outfd, 1);
	if (token->infd > 0)
		close(token->infd);
	if (token->outfd > 1)
		close(token->outfd);
	args = get_args(token->args);
	if (isbuiltin(args[0]))
	{
		free(envp);
		exit(ft_exec_builtins(shell, token));
	}
	else if (check_char('/', args[0]))
		execve(args[0], args, envp);
	else
		try_paths(shell, args, envp);
	free(envp);
	exit(127);
}

void	assign_pipes(t_token *token, int pipefds[2])
{
	pipe(pipefds);
	token->outfd = pipefds[1];
	token->next->infd = pipefds[0];
	token->pid = fork();
	if (!token->pid)
		close(pipefds[0]);
	else
	{
		if (token->infd > 0)
			close(token->infd);
		close(pipefds[1]);
	}
}

int	fuck_you_norminette(t_shell *shell)
{
	int	wpid;

	wpid = wait(&shell->lastreturn);
	if (wpid > 0)
		shell->lastreturn = WEXITSTATUS(shell->lastreturn);
	return (wpid);
}

void	write_pids(t_shell *shell)
{
	t_token	*tmptoken;
	int		i;

	if (g_pids)
		free(g_pids);
	i = 0;
	tmptoken = shell->token;
	while (tmptoken)
	{
		i++;
		tmptoken = tmptoken->next;
	}
	g_pids = ft_calloc(sizeof(int), i + 1);
	i = 0;
	tmptoken = shell->token;
	while (tmptoken)
	{
		g_pids[i] = tmptoken->pid;
		i++;
		tmptoken = tmptoken->next;
	}
}

void	fork_and_execute(t_shell *shell)
{
	int		pipefds[2];
	int		wpid;
	t_token	*token;

	token = shell->token;
	pipefds[0] = -1;
	pipefds[1] = -1;
	wpid = 1;
	while (token->pid && token->next)
	{
		assign_pipes(token, pipefds);
		if (token->pid)
			token = token->next;
	}
	if (token->pid)
		token->pid = fork();
	if (!token->pid)
		children(shell, token);
	else
	{
		if (pipefds[0] > 1)
			close(pipefds[0]);
		write_pids(shell);
		while (wpid > 0)
			wpid = fuck_you_norminette(shell);
	}
}

void	exec(t_shell *shell)
{
	t_token	*token;

	token = shell->token;
	if (!token->next && token->args && isbuiltin(token->args->arg))
	{
		g_pids = ft_calloc(sizeof(int), 1);
		shell->lastreturn = ft_exec_builtins(shell, token);
		return ;
	}
	else
	{
		handle_heredocs(shell);
		if (!g_pids)
			fork_and_execute(shell);
	}
	return ;
}

int	ft_exec_builtins(t_shell *shell, t_token *token)
{
	int		result;
	t_args	*args;

	args = token->args;
	result = 0;
	if (ft_strcmp(args->arg, "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args->arg, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args->arg, "cd") == 0)
		result = ft_cd(shell, args, shell->env);
	if (ft_strcmp(args->arg, "env") == 0)
		result = ft_env(shell->env);
	if (ft_strcmp(args->arg, "export") == 0)
		result = ft_export(shell);
	if (ft_strcmp(args->arg, "unset") == 0)
		result = ft_unset(shell);
	if (ft_strcmp(args->arg, "exit") == 0)
		ft_exit_minishell(shell);
	return (result);
}
