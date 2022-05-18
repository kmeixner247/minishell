/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesDONTUSETHIS.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:36 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/18 14:05:34 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	trypaths(char **args, char **envp)
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

void	children(t_token *token, char **envp)
{
	int		tempinfd;
	int		tempoutfd;
	char	**args;
	mode_t	openmodes;

	openmodes = S_IRWXU | S_IRWXG | S_IRWXO;
	tempinfd = -1;
	tempoutfd = -1;
	while (token->redir)
	{
		if (token->redir->id == 1)
		{
			if (tempinfd > 0)
				close(tempinfd);
			tempinfd = open(token->redir->filename, O_RDONLY);
		}
		else if (token->redir->id == 2)
			fprintf(stderr, "This is where here_doc will happen\n");
		else if (token->redir->id == 3)
		{
			if (tempoutfd > 0)
				close(tempoutfd);
			tempoutfd = open(token->redir->filename, O_WRONLY | O_CREAT | O_TRUNC, openmodes);
		}
		else if (token->redir->id == 4)
		{
			if (tempoutfd > 0)
				close(tempoutfd);
			tempoutfd = open(token->redir->filename, O_WRONLY | O_CREAT | O_APPEND, openmodes);
		}
		token->redir = token->redir->next;
	}
	if (tempinfd > 0)
		token->infd = tempinfd;
	if (tempoutfd > 0)
		token->outfd = tempoutfd;
	dup2(token->infd, 0);
	dup2(token->outfd, 1);
	if (token->infd != 0)
		close(token->infd);
	if (token->outfd != 1)
		close(token->outfd);
	args = get_args(token);
	trypaths(args, envp);
	fprintf(stderr, "Hey! I am a child and my first argument is %s\n", token->args->arg);
	exit(0);
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
	while(pid && token->next)
	{
		pipe(pipefds);
		token->outfd = pipefds[1];
		token->next->infd = pipefds[0];
		pid = fork();
		if (!pid)
		{
			close(pipefds[0]);
		}
		else
		{
			if (token->infd > 0)
				close(token->infd);
			close(pipefds[1]);
			token = token->next;
		}
	}
	if (pid)
		pid = fork();
	//basically here I can start executing shit
	if (!pid)
	{
		children(token, envp);
	}
	else
	{
		fprintf(stderr, "I am the almighty parent and my pid is \"%d\"\n", pid);
		close(pipefds[0]);
		while (wpid > 0)
			wpid = wait(NULL);
	}
	return ;
}
