/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:06:39 by jsubel            #+#    #+#             */
/*   Updated: 2021/12/08 09:37:48 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dst = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		dst[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	dst[i + ft_strlen(s1)] = '\0';
	return (dst);
}
