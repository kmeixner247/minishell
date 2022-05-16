/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:16:02 by jsubel            #+#    #+#             */
/*   Updated: 2022/01/17 11:18:14 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
	current = ft_lstlast(*lst);
	current->next = new;
	}
}

/* void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	new->next = NULL;
	last = ft_lstlast(*lst);
	last->next = new;
}*/