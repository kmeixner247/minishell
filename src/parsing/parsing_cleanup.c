/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:16:50 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/30 11:21:24 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ft_redir_cleanup(t_token *token)
{
	t_redir	*redirtmp;

	while (token->redir)
	{
		redirtmp = token->redir;
		token->redir = token->redir->next;
		free(redirtmp->filename);
		free(redirtmp);
	}
}

static void	ft_args_cleanup(t_token *token)
{
	t_args	*argstmp;

	while (token->args)
	{
		argstmp = token->args;
		token->args = token->args->next;
		free(argstmp->arg);
		free(argstmp);
	}
}

int	parsing_cleanup(t_shell *shell)
{
	t_token	*tokentmp;
	t_token	*token;

	token = shell->token;
	while (token)
	{
		ft_redir_cleanup(token);
		ft_args_cleanup(token);
		tokentmp = token;
		token = token->next;
		free(tokentmp);
	}
	shell->token = NULL;
	return (0);
}
