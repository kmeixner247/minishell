/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:38:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/27 12:19:05 by kmeixner         ###   ########.fr       */
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

int	here_doc_parent(char *tempfilepath, int pid, int infd, int outfd)
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
		infd = open(tempfilepath, O_RDONLY);
	}
	unlink(tempfilepath);
	return (infd);
}

int	here_doc(t_shell *shell, char *delimiter)
{
	int		fds[2];
	char	*tempfilepath;
	int		openflags;
	int		pid;
	int		status;

	openflags = O_WRONLY | O_CREAT | O_EXCL | O_TRUNC;
	tempfilepath = ft_strjoin3("/tmp/minishell-thd", ft_itoa((int)&delimiter));
	fds[1] = open(tempfilepath, openflags, 0600);
	pid = fork();
	if (!pid)
	{
		here_doc_child(shell, delimiter, fds[1]);
		exit(0);
	}	
	else
		return (here_doc_parent(tempfilepath, pid, fds[0], fds[1]));
}
