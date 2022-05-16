/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:07:48 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 14:40:41 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_args	*new_args(void)
{
	t_args	*newargs;

	newargs = ft_calloc(sizeof(t_args), 1);
	if (!newargs)
		return (NULL);
	newargs->arg = NULL;
	newargs->next = NULL;
	return (newargs);
}

void	args_addback(t_args **start, t_args *new)
{
	t_args	*temp;

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
