/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:06:39 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/16 13:34:37 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char *s2)
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
	free(s3);
	return (dst);
}
