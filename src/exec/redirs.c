/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:17:00 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/24 13:04:03 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	redir_input(t_shell *shell, t_redir *redir, int tempinfd, char **envp)
{
	if (tempinfd > 0)
		close(tempinfd);
	if (redir->id == 1)
		tempinfd = open(redir->filename, O_RDONLY);
	else if (redir->id == 2)
		tempinfd = here_doc(shell, redir->filename, envp);
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

static void	handle_redirs_single(t_shell *shell, t_token *token, char **envp)
{
	int		tempinfd;
	int		tempoutfd;
	t_redir	*tmp;

	tmp = token->redir;
	tempinfd = -1;
	tempoutfd = -1;
	while (tmp)
	{
		if (tmp->id == 1 || tmp->id == 2)
			tempinfd = redir_input(shell, tmp, tempinfd, envp);
		else if (tmp->id == 3 || tmp->id == 4)
			tempoutfd = redir_output(tmp, tempoutfd);
		tmp = tmp->next;
	}
	if (tempinfd > 0)
		token->infd = tempinfd;
	if (tempoutfd > 0)
		token->outfd = tempoutfd;
}

void	handle_redirs(t_shell *shell)
{
	t_token	*tmp;
	char	**envv;

	envv = get_env(shell->env);
	tmp = shell->token;
	while (tmp)
	{
		handle_redirs_single(shell, tmp, envv);
		tmp = tmp->next;
	}
	free(envv);
}
