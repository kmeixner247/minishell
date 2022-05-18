/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesDONTUSETHIS.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:36 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/18 10:48:42 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	children(t_token *token, char **envp)
{
	int	tempfdin;
	int	tempfdout;

	tempfdin = -1;
	tempfdout = -1;
	if (token->infd > 0)
	{
		dup2(token->infd, 0);
		close(token->infd);
	}	
	if (token->outfd > 0)
	{	
		dup2(token->outfd, 1);
		close(token->outfd);
	}
	while (token->redir)
	{
		if (token->redir->id == 1)
		{
			if (tempfdin > 0)
				close(tempfdin);
			tempfdin = open(token->redir->filename, O_RDONLY);
		}
		else if (token->redir->id == 2)
			fprintf(stderr, "This is where here_doc will happen\n");
		else if (token->redir->id == 3)
		{
			if (tempfdout > 0)
				close(tempfdout);
			tempfdout = open(token->redir->filename, O_WRONLY | O_CREAT | O_TRUNC);
		}
		else if (token->redir->id == 4)
		{
			if (tempfdout > 0)
				close(tempfdout);
			tempfdout = open(token->redir->filename, O_WRONLY | O_CREAT | O_APPEND);
		}
	}
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
		fprintf(stderr, "I am the almighty parent and my pid is %d\n", pid);
		close(pipefds[0]);
		while (wpid > 0)
			wpid = wait(NULL);
	}
	return ;
}
