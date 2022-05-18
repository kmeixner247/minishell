/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesDONTUSETHIS.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:36 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/18 19:02:04 by kmeixner         ###   ########.fr       */
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

int	here_doc(char *delimiter)
{
	int		writefd;
	int		readfd;
	char	*line;
	char	*tempfilepath;
	int		openflags;

	openflags = O_WRONLY | O_CREAT | O_EXCL | O_TRUNC;
	tempfilepath = ft_strjoin3("/tmp/minishell-thd", ft_itoa((int)&delimiter));
	writefd = open(tempfilepath, openflags, 0600);
	line = readline("> ");
	while (42)
	{
		if (ft_strlen(delimiter) == ft_strlen(line) && !ft_strncmp(delimiter, line, ft_strlen(line)) || !line)
			break ;
		write(writefd, line, ft_strlen(line));
		write(writefd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	readfd = open(tempfilepath, O_RDONLY);
	close(writefd);
	unlink(tempfilepath);
	return (readfd);
}

int	redir_input(t_redir *redir, int tempinfd)
{
	if (tempinfd > 0)
		close(tempinfd);
	if (redir->id == 1)
		tempinfd = open(redir->filename, O_RDONLY);
	else if (redir->id == 2)
		tempinfd = here_doc(redir->filename);
	return (tempinfd);
}

int	redir_output(t_redir *redir, int tempoutfd)
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

void	handle_redirs(t_token *token, char **envp)
{
	int		tempinfd;
	int		tempoutfd;

	tempinfd = -1;
	tempoutfd = -1;
	while (token->redir)
	{
		if (token->redir->id == 1 || token->redir->id == 2)
			tempinfd = redir_input(token->redir, tempinfd);
		else if (token->redir->id == 3 || token->redir->id == 4)
			tempoutfd = redir_output(token->redir, tempoutfd);
		token->redir = token->redir->next;
	}
	if (tempinfd > 0)
		token->infd = tempinfd;
	if (tempoutfd > 0)
		token->outfd = tempoutfd;
}

void	cycle_tokens(t_token *token, char **envp)
{
	while (token)
	{
		handle_redirs(token, envp);
		token = token->next;
	}
}

void	children(t_token *token, char **envp)
{
	char	**args;

	dup2(token->infd, 0);
	dup2(token->outfd, 1);
	if (token->infd != 0)
		close(token->infd);
	if (token->outfd != 1)
		close(token->outfd);
	args = get_args(token);
	try_paths(args, envp);
	exit(0);
}

void	fork_and_execute(t_token *token, char **envp)
{
	int	pid;
	int	pipefds[2];
	int	wpid;

	pid = 1;
	while (pid && token->next)
	{
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
			close(pipefds[1]);
			token = token->next;
		}
	}
	if (pid)
		pid = fork();
	if (!pid)
		children(token, envp);
	else
	{
		close(pipefds[0]);
		while (wpid > 0)
			wpid = wait(NULL);
	}
}

void	exectests(t_token *token, char **envp)
{
	int	pid;
	int	pipefds[2];
	int	wpid;

	pid = 1;
	if (!token->next)
	{
		fprintf(stderr, "no pipes here\n");
		return ;
	}
	else
	{
		cycle_tokens(token, envp);
		fork_and_execute(token, envp);
	}
	return ;
}
