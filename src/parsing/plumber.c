/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:29:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/15 14:02:58 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	countpipes(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		str += quote_skipper(str);
		if (*str == 124)
			count++;
		if (*str)
			str++;
	}
	return (count);
}

char	**plumber(char *str)
{
	char	**retarr;
	int		pipes;
	int		i;

	pipes = countpipes(str);
	retarr = ft_calloc(sizeof(char *), pipes + 2);
	i = 0;
	while (i <= pipes)
	{
		retarr[i] = str;
		while (*str && *str != 124)
		{
			str += quote_skipper(str);
			if (*str && *str != 124)
				str++;
		}
		if (*str == 124)
		{
			*str = 0;
			str++;
		}
		i++;
	}
	retarr[i] = NULL;
	return (retarr);
}
