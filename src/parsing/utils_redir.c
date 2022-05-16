/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:06:15 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 14:40:53 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_redir	*new_redir(void)
{
	t_redir	*newredir;

	newredir = ft_calloc(sizeof(t_redir), 1);
	if (!newredir)
		return (NULL);
	newredir->id = 0;
	newredir->filename = NULL;
	newredir->next = (NULL);
	return (newredir);
}

void	redir_addback(t_redir **start, t_redir *new)
{
	t_redir	*temp;

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
