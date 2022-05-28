/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:38:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/27 21:40:00 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	here_doc_child(t_shell *shell, char *delimiter, int outfd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGUSR1, hd_newline);
	line = readline("> ");
	while (42)
	{
		if (!line || !ft_strcmp(delimiter, line))
			break ;
		line = accountant_hd(shell, line);
		write(outfd, line, ft_strlen(line));
		write(outfd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(outfd);
}

void	here_doc_parent(int pid, int outfd)
{
	int	status;

	g_pids = ft_calloc(3, sizeof(int));
	g_pids[0] = -15;
	g_pids[1] = pid;
	close(outfd);
	wait(&status);
	if (!status)
	{
		free(g_pids);
		g_pids = NULL;
	}
}

void	here_doc(t_shell *shell, t_redir *redir)
{
	int		fd;
	char	*path;
	int		openflags;
	int		pid;
	char	*delimiter;

	redir->filename = replace_string(redir->filename);
	delimiter = redir->filename;
	openflags = O_WRONLY | O_CREAT | O_EXCL | O_TRUNC;
	path = ft_strjoin3("/tmp/minishell-thd", ft_itoa((int)&(redir->filename)));
	fd = open(path, openflags, 0600);
	pid = fork();
	if (!pid)
	{
		here_doc_child(shell, delimiter, fd);
		exit(0);
	}	
	else
	{
		here_doc_parent(pid, fd);
		redir->filename = strdup(path);
		redir->id = 5;
	}
}

void	handle_heredocs(t_shell *shell)
{
	t_token	*tmptoken;
	t_redir	*tmpredir;

	tmptoken = shell->token;
	while (tmptoken)
	{
		tmpredir = tmptoken->redir;
		while (tmpredir)
		{
			if (tmpredir->id == 2)
				here_doc(shell, tmpredir);
			tmpredir = tmpredir->next;
		}
		tmptoken = tmptoken->next;
	}
}
