/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesDONTUSETHIS.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:26:36 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 17:24:44 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	openthosegoddamnpipesbro(t_token *token)
{
	int	pipefds[2];

	while (token->next)
	{
		pipe(pipefds);
		token->outfd = pipefds[1];
		token->next->infd = pipefds[0];
	}
}

void	exectests(t_token *token, t_env *envv) 
{
	openthosegoddamnpipesbro(token);
	return ;
}
 