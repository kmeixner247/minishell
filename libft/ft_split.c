/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel < jsubel@student.42wolfsburg.de >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:27:03 by jsubel            #+#    #+#             */
/*   Updated: 2021/11/29 16:33:15 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	marker;
	size_t	nbr_of_words;

	i = 0;
	marker = 0;
	nbr_of_words = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && marker == 0)
		{
			marker = 1;
			nbr_of_words++;
		}
		else if (s[i] == c)
			marker = 0;
		i++;
	}
	return (nbr_of_words);
}

static size_t	ft_word_len(const char *s, char c, size_t i)
{
	size_t	nbr_of_letters;

	nbr_of_letters = 0;
	while (s[i] != c && s[i] != '\0' && i < ft_strlen(s))
	{	
		nbr_of_letters++;
		i++;
	}
	return (nbr_of_letters);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	**lst;

	if (s == 0)
		return (0);
	i = 0;
	j = 0;
	lst = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!lst)
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		lst[i] = (char *)malloc(sizeof(char) * ft_word_len(s, c, j) + 1);
		if (!lst[i])
			free (lst[i]);
		ft_strlcpy(lst[i], &s[j], ft_word_len(s, c, j) + 1);
		j = j + ft_word_len(s, c, j);
		i++;
	}
	lst[i] = 0;
	return (lst);
}
