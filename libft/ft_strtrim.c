/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:04:47 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/05 16:27:24 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	find_start(const char *s1, const char *set)
{
	size_t	start;

	start = 0;
	while (ft_strchr(set, s1[start]) != 0 && start < ft_strlen(s1))
		start++;
	return (start);
}

static size_t	find_end(const char *s1, const char *set)
{
	size_t	end;

	end = ft_strlen(s1);
	while (ft_strrchr(set, s1[end]) != 0 && end > 1)
		end--;
	return (end + 1);

}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		start;
	size_t		end;
	char		*res;

	if (!s1 || !set)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!res)
		return (NULL);
	s1 = s1 + start;
	ft_strlcpy(res, s1, end - start + 1);
	return (res);
}
