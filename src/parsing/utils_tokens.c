/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:09:39 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 14:40:57 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token	*new_token(void)
{
	t_token	*newtoken;

	newtoken = ft_calloc(sizeof(t_token), 1);
	if (!newtoken)
		return (NULL);
	newtoken->args = NULL;
	newtoken->redir = NULL;
	newtoken->next = NULL;
	return (newtoken);
}

void	token_addback(t_token **start, t_token *new)
{
	t_token	*temp;

	temp = *start;
	if (!temp)
	{
		*start = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
