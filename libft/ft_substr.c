/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:56:54 by jsubel            #+#    #+#             */
/*   Updated: 2021/12/09 15:30:43 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) < start)
	{
		dst = ft_strdup("");
		return (dst);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dst = malloc(sizeof(char) * (len + 1));
	if (!s || !dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
