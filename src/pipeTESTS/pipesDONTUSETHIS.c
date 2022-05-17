/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesDONTUSETHIS.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:36 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 20:19:04 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	exectests(t_token *token) 
{
	int	pid;
	int	pipefds[2];

	pid = 0;
	if (!token->next)
	{
		printf("no pipes here\n");
		return ;
	}
	while(!pid && token->next)
	{
		pipe(pipefds);
		token->outfd = pipefds[1];
		token->next->infd = pipefds[0];
		pid = fork();
		if (pid)
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
	if (!pid)
		pid = fork();
	if (pid)
	{
		if (token->infd > 0)
			close(token->infd);
		if (token->outfd > 0)
			close(token->outfd);
		printf("Hey! I am a child, my pid is %d and my first argument is %s\n", pid, token->args->arg);
		exit(0);
	}
	else
	{
		printf("I am the almighty parent and my pid is %d\n", pid);
		wait(NULL);
		wait(NULL);
		wait(NULL);
		close(pipefds[0]);
	}
	return ;
}
