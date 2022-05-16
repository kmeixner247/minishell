/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:50:24 by jsubel            #+#    #+#             */
/*   Updated: 2021/11/22 14:19:30 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;
	size_t			i;

	i = 0;
	dst = (unsigned char *)b;
	while (len > 0)
	{
		dst[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
