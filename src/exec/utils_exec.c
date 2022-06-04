/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:03:34 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/04 11:26:55 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

void	try_paths(t_shell *shell, char **args, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	if (!args[0][0])
		return ;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		paths = ft_split(envp[i], ':');
	i = 0;
	while (paths && paths[i])
	{
		paths[i] = ft_strjoin2(paths[i], "/");
		paths[i] = ft_strjoin2(paths[i], args[0]);
		execve(paths[i], args, envp);
		if (errno == EACCES)
			break ;
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
