/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:29:29 by jsubel            #+#    #+#             */
/*   Updated: 2021/12/08 09:39:39 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_element;

	if (!lst || !del)
		return ;
	next_element = (*lst);
	while (*lst)
	{
		next_element = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = next_element;
	}
}
