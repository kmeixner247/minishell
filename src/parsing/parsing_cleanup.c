/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:16:50 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 12:18:41 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	parsing_cleanup(t_token *token)
{
	t_redir	*redirtmp;
	t_args	*argstmp;
	t_token	*tokentmp;

	while (token)
	{
		while (token->redir)
		{
			redirtmp = token->redir;
			token->redir = token->redir->next;
			free(redirtmp->filename);
			free(redirtmp);
		}
		while (token->args)
		{
			argstmp = token->args;
			token->args = token->args->next;
			free(argstmp->arg);
			free(argstmp);
		}
		tokentmp = token;
		token = token->next;
		free(tokentmp);
	}
	return (0);
}