/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:46:40 by jsubel            #+#    #+#             */
/*   Updated: 2021/12/09 10:01:39 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_element;

	if (!lst || !f)
		return (NULL);
	new_element = ft_lstnew(f(lst->content));
	if (!new_element)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	new_lst = new_element;
	lst = lst->next;
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (!new_element)
			ft_lstdelone(new_lst, del);
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_element);
	}
	return (new_lst);
}
