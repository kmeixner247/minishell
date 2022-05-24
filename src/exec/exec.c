/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/24 16:22:27 by kmeixner         ###   ########.fr       */
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

void	children(t_shell *shell)
{
	char	**args;
	char	**envp;

	envp = get_env(shell->env);
	dup2(shell->token->infd, 0);
	dup2(shell->token->outfd, 1);
	if (shell->token->infd > 0)
		close(shell->token->infd);
	if (shell->token->outfd > 1)
		close(shell->token->outfd);
	args = get_args(shell->token->args);
	if (isbuiltin(args[0]))
	{
		free(envp);
		exit(ft_exec_builtins(shell));
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
	if (token->outfd == 1)
		token->outfd = pipefds[1];
	if (token->next->infd == 0)
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

void	fork_and_execute(t_shell *shell)
{
	int	pipefds[2];
	int	wpid;

	pipefds[0] = -1;
	pipefds[1] = -1;
	wpid = 1;
	while (shell->token->pid && shell->token->next)
	{
		assign_pipes(shell->token, pipefds);
		if (shell->token->pid)
			shell->token = shell->token->next;
	}
	if (shell->token->pid)
		shell->token->pid = fork();
	if (!shell->token->pid)
		children(shell);
	else
	{
		if (pipefds[0] > 1)
			close(pipefds[0]);
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
		shell->lastreturn = ft_exec_builtins(shell);
		return ;
	}
	else
	{
		handle_redirs(shell);
		fork_and_execute(shell);
	}
	return ;
}

int	ft_exec_builtins(t_shell *shell)
{
	int		result;
	t_args	*args;

	args = shell->token->args;
	result = 0;
	if (ft_strcmp(args->arg, "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args->arg, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args->arg, "cd") == 0)
		result = ft_cd(shell, args);
	if (ft_strcmp(args->arg, "env") == 0)
		result = ft_env(shell->env);
	if (ft_strcmp(args->arg, "export") == 0)
		result = ft_export(shell);
	if (ft_strcmp(args->arg, "unset") == 0)
		result = ft_unset(shell);
	if (ft_strcmp(args->arg, "exit") == 0)
		result = ft_exit_minishell(shell);
	return (result);
}
