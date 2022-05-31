/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/31 22:25:22 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ft_meta_acc_wild_quote(t_shell *shell, t_token *token)
{
	meta_accountant(shell, token);
	meta_args_wildcard(token);
	quote_handler(token);
}

void	exec_children(t_shell *shell, t_token *token)
{
	char	**args;
	char	**envp;

	if (handle_redirs_single(shell, token))
		exit(1);
	envp = get_env(shell->env);
	ft_meta_acc_wild_quote(shell, token);
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
	ft_error(shell, args[0], ERRNO_NOT_FOUND);
}

void	exec_parent(t_shell *shell, int fd)
{
	int	wpid;

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
		ft_meta_acc_wild_quote(shell, token);
		tempfd = dup(1);
		dup2(token->outfd, 1);
		shell->lastreturn = ft_exec_builtins(shell, token);
		if (token->infd > 0)
			close(token->infd);
		if (token->outfd > 1)
			close(token->outfd);
		dup2(tempfd, 1);
		return ;
	}
	else if (!g_pids)
		fork_and_execute(shell);
	return ;
}
