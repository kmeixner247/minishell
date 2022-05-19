/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesDONTUSETHIS.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:36 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/19 13:07:37 by kmeixner         ###   ########.fr       */
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
		if (ft_strlen(delimiter) == ft_strlen(line) && \
			!ft_strncmp(delimiter, line, ft_strlen(line)) || !line)
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

void	handle_redirs_single(t_token *token, char **envp)
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
			tempinfd = redir_input(tmp, tempinfd);
		else if (tmp->id == 3 || tmp->id == 4)
			tempoutfd = redir_output(tmp, tempoutfd);
		tmp = tmp->next;
	}
	if (tempinfd > 0)
		token->infd = tempinfd;
	if (tempoutfd > 0)
		token->outfd = tempoutfd;
}

void	handle_redirs(t_token *token, char **envp)
{
	t_token	*tmp;
	
	tmp = token;
	while (tmp)
	{
		handle_redirs_single(tmp, envp);
		tmp = tmp->next;
	}
}

void	children(t_token *token, char **envp)
{
	char	**args;

	dup2(token->infd, 0);
	dup2(token->outfd, 1);
	if (token->infd > 0)
		close(token->infd);
	if (token->outfd > 1)
		close(token->outfd);
	args = get_args(token);
	if (check_char('/', args[0]))
		execve(args[0], args, envp);
	else
		try_paths(args, envp);
	exit(0);
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
		close(pipefds[1]);
	return (pid);
}

void	fork_and_execute(t_token *token, char **envp)
{
	int	pid;
	int	pipefds[2];
	int	wpid;

	pipefds[0] = -1;
	pipefds[1] = -1;
	pid = 1;
	wpid = 1;
	while (pid && token->next)
	{
		pid = assign_pipes(token, pipefds);
		if (pid)
			token = token->next;
	}
	if (pid)
		pid = fork();
	if (!pid)
		children(token, envp);
	else
	{
		if (pipefds[0] > 0)
			close(pipefds[0]);
		while (wpid > 0)
			wpid = wait(NULL);
	}
}

int	isbuiltin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || \
		!ft_strcmp(arg, "cd") || \
		!ft_strcmp(arg, "pwd") || \
		!ft_strcmp(arg, "export") || \
		!ft_strcmp(arg, "unset") || \
		!ft_strcmp(arg, "env") || \
		!ft_strcmp(arg, "exit"))
		return (1);
	else
		return (0);
}

void	exectests(t_token *token, char **envp)
{
	int	pid;
	int	pipefds[2];
	int	wpid;

	pid = 1;
	if (!token->next && token->args && isbuiltin(token->args->arg))
	{
		fprintf(stderr, "%s dies das\n", token->args->arg);
		return ;
	}
	else
	{
		handle_redirs(token, envp);
		fork_and_execute(token, envp);
	}
	return ;
}
