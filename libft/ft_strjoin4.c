/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:06:39 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/08 10:37:53 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin4(char *s1, char *s2)
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
	free(s1);
	free(s2);
	return (dst);
}
