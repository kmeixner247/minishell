/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:29:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/25 09:07:52 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//counts all non-escaped pipe characters within str
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

//cuts the inputstring by pipes and returns a NULL-terminated string array
//with each element being one section
char	**plumber(char *str)
{
	char	**retarr;
	int		pipes;
	int		i;

	pipes = countpipes(str);
	retarr = ft_calloc(pipes + 2, sizeof(char *));
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
