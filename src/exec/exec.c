/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 11:58:46 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	try_paths(char **args, char **envp)
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
	args = get_args(shell->token);
	if (check_char('/', args[0]))
		execve(args[0], args, envp);
	else
		try_paths(args, envp);
	free(envp);
	exit(1);
}

int	assign_pipes(t_token *token, int pipefds[2])
{
	int	pid;

	pipe(pipefds);
	if (token->outfd == 1)
		token->outfd = pipefds[1];
	if (token->next->infd == 0)
		token->next->infd = pipefds[0];
	pid = fork();
	if (!pid)
		close(pipefds[0]);
	else
	{
		if (token->infd > 0)
			close(token->infd);
		close(pipefds[1]);
	}
	return (pid);
}

void	fork_and_execute(t_shell *shell)
{
	int	pid;
	int	pipefds[2];
	int	wpid;

	pipefds[0] = -1;
	pipefds[1] = -1;
	pid = 1;
	wpid = 1;
	while (pid && shell->token->next)
	{
		pid = assign_pipes(shell->token, pipefds);
		if (pid)
			shell->token = shell->token->next;
	}
	if (pid)
		pid = fork();
	if (!pid)
		children(shell);
	else
	{
		if (pipefds[0] > 1)
			close(pipefds[0]);
		while (wpid > 0)
			wpid = wait(&shell->lastreturn);
	}
}

void	exec(t_shell *shell)
{
	int		pid;
	int		pipefds[2];
	t_token	*token;

	token = shell->token;
	pid = 1;
	if (!token->next && token->args && isbuiltin(token->args->arg))
	{
		fprintf(stderr, "%s dies das\n", token->args->arg);
		ft_exec_builtins(token->args, shell->env);
		return ;
	}
	else
	{
		handle_redirs(shell);
		fork_and_execute(shell);
	}
	return ;
}

int	ft_exec_builtins(t_args *args, t_env *env)
{
	int	result;

	result = 0;
	if (ft_strcmp(args->arg, "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args->arg, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args->arg, "cd") == 0)
		result = ft_cd(args, env);
	if (ft_strcmp(args->arg, "env") == 0)
		result = ft_env(env);
	if (ft_strcmp(args->arg, "export") == 0)
		result = ft_export(&env, get_env(env));
	if (ft_strcmp(args->arg, "unset") == 0)
		result = ft_unset(&env, get_env(env));
	return (result);
}
