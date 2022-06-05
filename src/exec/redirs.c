/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:17:00 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/05 21:55:06 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	redir_input(t_shell *shell, t_redir *redir, int tempinfd)
{
	if (tempinfd > 0)
		close(tempinfd);
	tempinfd = open(redir->filename, O_RDONLY);
	if (tempinfd < 0)
		return (ft_error_msg(shell, redir->filename, 0));
	if (redir->id == 5)
		unlink(redir->filename);
	return (tempinfd);
}

static int	redir_output(t_shell *shell, t_redir *redir, int tempoutfd)
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
	if (tempoutfd < 0)
		return (ft_error_msg(shell, redir->filename, 0));
	return (tempoutfd);
}

static void	ft_change_fd(t_token *token, int tempinfd, int tempoutfd)
{
	if (tempinfd > 0)
		token->infd = tempinfd;
	if (tempoutfd > 1)
		token->outfd = tempoutfd;
}

int	handle_redirs_single(t_shell *shell, t_token *token)
{
	int		tempinfd;
	int		tempoutfd;
	t_redir	*tmp;

	tmp = token->redir;
	tempinfd = token->infd;
	tempoutfd = token->outfd;
	while (tmp)
	{
		tmp->filename = accountant(shell, tmp->filename);
		if (redir_wildcard(shell, tmp))
			return (1);
		tmp->filename = replace_string(tmp->filename);
		if (tmp->id == 1 || tmp->id == 5)
			tempinfd = redir_input(shell, tmp, tempinfd);
		else if (tmp->id == 3 || tmp->id == 4)
			tempoutfd = redir_output(shell, tmp, tempoutfd);
		tmp = tmp->next;
	}
	ft_change_fd(token, tempinfd, tempoutfd);
	if ((tempinfd == -1 || tempoutfd == -1))
		return (1);
	return (0);
}
