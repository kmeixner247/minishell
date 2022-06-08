/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/08 15:49:05 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	prepare_child(t_shell *shell, t_token *token)
{
	if (handle_redirs_single(shell, token) || !token->args)
	{
		if (token->infd > 0)
			close(token->infd);
		if (token->outfd > 1)
			close(token->outfd);
		exit(1);
	}
	ft_meta_wild_quote(token);
	dup2(token->infd, 0);
	dup2(token->outfd, 1);
	if (token->infd > 0)
		close(token->infd);
	if (token->outfd > 1)
		close(token->outfd);
}

void	exec_children(t_shell *shell, t_token *token)
{
	char	**args;
	char	**envp;
	int		status;

	prepare_child(shell, token);
	status = -1;
	envp = get_env(shell->env);
	args = get_args(token->args);
	if (isbuiltin(args[0]))
		status = ft_exec_builtins(shell, token, -1);
	else if (check_char('/', args[0]))
		execve(args[0], args, envp);
	else
		try_paths(args, envp);
	if (status == -1)
		status = notfound_or_isdir(shell, args[0]);
	free(args);
	free(envp);
	exit(status);
}

void	exec_parent(t_shell *shell, int fd)
{
	int	wpid;

	signal(SIGINT, SIG_IGN);
	wpid = 1;
	if (fd > 1)
		close(fd);
	write_pids(shell);
	while (wpid > 0)
	{
		wpid = wait(&shell->lastreturn);
		if (wpid > 0)
			shell->lastreturn = WEXITSTATUS(shell->lastreturn);
	}
	signal(SIGINT, handle_sigint);
}

void	fork_and_execute(t_shell *shell)
{
	int		pipefds[2];
	t_token	*token;

	token = shell->token;
	pipefds[0] = -1;
	pipefds[1] = -1;
	while (token->pid && token->next)
	{
		assign_pipes(token, pipefds);
		if (token->pid)
			token = token->next;
	}
	if (token->pid)
		token->pid = fork();
	if (!token->pid)
		exec_children(shell, token);
	else
		exec_parent(shell, pipefds[0]);
}

void	exec(t_shell *shell)
{
	t_token	*token;
	int		tempfd;

	token = shell->token;
	if (!token->next && token->args && isbuiltin(token->args->arg))
	{
		g_pids = ft_calloc(sizeof(int), 1);
		if (handle_redirs_single(shell, token))
			return ;
		ft_meta_wild_quote(token);
		tempfd = dup(1);
		dup2(token->outfd, 1);
		shell->lastreturn = ft_exec_builtins(shell, token, tempfd);
		if (token->infd > 0)
			close(token->infd);
		if (token->outfd > 1)
			close(token->outfd);
		dup2(tempfd, 1);
		close(tempfd);
		return ;
	}
	else if (!g_pids)
		fork_and_execute(shell);
	return ;
}
