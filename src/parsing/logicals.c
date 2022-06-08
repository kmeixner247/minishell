/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logicals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:07:10 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/08 13:02:43 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	init_values(int *i, int *level, int *sing, int *doub)
{
	i = 0;
	level = 0;
	*sing = -1;
	*doub = -1;
}

int	find_closing_parenthesis(char *str)
{
	int	i;
	int	level;
	int	sing;
	int	doub;

	init_values(&i, &level, &sing, &doub);
	while (str[i])
	{
		if (str[i] == 41 && sing == -1 && doub == -1)
		{
			if (level == 1)
				break ;
			else
				level--;
		}
		else if (str[i] == 34 && sing == -1)
			doub *= -1;
		else if (str[i] == 39 && doub == -1)
			sing *= -1;
		else if (str[i] == 40 && doub == -1 && sing == -1)
			level++;
		i++;
	}
	return (i);
}

int	find_size(char *str)
{
	char	*end;

	if (!str)
		return (0);
	end = has_logical(str);
	if (end > str)
		end--;
	while (end > str && *end == 32)
		end--;
	if (end != str)
		end++;
	return (end - str);
}

int	set_operator(char *str)
{
	if (*str == 38 && *(str + 1) == 38)
		return (1);
	else if (*str == 124 && *(str + 1) == 124)
		return (2);
	else
		return (0);
}

int	set_parentheses_flag(char **str, int *size)
{
	if (**str == 40)
	{
		(*str)++;
		*size -= 2;
		return (1);
	}
	else
		return (0);
}
