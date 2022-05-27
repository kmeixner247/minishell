/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:17:00 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/27 15:57:51 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	redir_input(t_shell *shell, t_redir *redir, int tempinfd)
{
	if (tempinfd > 0)
		close(tempinfd);
	tempinfd = open(redir->filename, O_RDONLY);
	if (redir->id == 5)
		unlink(redir->filename);
	return (tempinfd);
}

static int	redir_output(t_redir *redir, int tempoutfd)
{
	int		openflags;
	mode_t	openmodes;

	openflags = 0;
	openmodes = S_IRWXU | S_IRWXG | S_IRWXO;
	if (tempoutfd > 1)
		close(tempoutfd);
	if (redir->id == 3)
		openflags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir->id == 4)
		openflags = O_WRONLY | O_CREAT | O_APPEND;
	tempoutfd = open(redir->filename, openflags, openmodes);
	return (tempoutfd);
}

void	handle_redirs_single(t_shell *shell, t_token *token)
{
	int		tempinfd;
	int		tempoutfd;
	t_redir	*tmp;

	tmp = token->redir;
	tempinfd = -1;
	tempoutfd = -1;
	while (tmp)
	{
		if (tmp->id == 1 || tmp->id == 5)
			tempinfd = redir_input(shell, tmp, tempinfd);
		else if (tmp->id == 3 || tmp->id == 4)
			tempoutfd = redir_output(tmp, tempoutfd);
		tmp = tmp->next;
	}
	token->infd = tempinfd;
	token->outfd = tempoutfd;
}

// void	handle_redirs(t_shell *shell)
// {
// 	t_token	*tmp;
// 	char	**envv;

// 	envv = get_env(shell->env);
// 	tmp = shell->token;
// 	while (tmp && !g_pids)
// 	{
// 		handle_redirs_single(shell, tmp, envv);
// 		tmp = tmp->next;
// 	}
// 	free(envv);
// }
