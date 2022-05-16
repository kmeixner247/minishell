/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:12:21 by jsubel            #+#    #+#             */
/*   Updated: 2021/12/06 10:09:55 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	find_end_dest;
	unsigned int	counter_src;
	unsigned int	len_dest;
	unsigned int	len_src;

	counter_src = 0;
	len_dest = 0;
	while (dest[len_dest] != '\0' && len_dest < size)
		len_dest++;
	len_src = ft_strlen(src);
	if (size == 0 || size < ft_strlen(dest))
		return (len_dest + len_src);
	find_end_dest = len_dest;
	while (src[counter_src] != '\0' && find_end_dest < size)
	{
		if (find_end_dest >= size - 1)
			break ;
		dest[find_end_dest] = src[counter_src];
		find_end_dest++;
		counter_src++;
	}
	dest[find_end_dest] = '\0';
	return (len_dest + len_src);
}
