/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:58:46 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/31 22:06:58 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * @brief incredibly important function
 * handle with extreme care
 */
void	ft_important_function(t_args *args)
{
	free(args->arg);
	free(args);
}

/**
 * @brief check if function has wildcard character
 	outside of single or double quotes
*/
int	haswildcard(char *str)
{
	int	sing;
	int	doub;

	sing = -1;
	doub = -1;
	while (*str)
	{
		if (*str == 39 && doub == -1)
			sing *= -1;
		else if (*str == 34 && sing == -1)
			doub *= -1;
		if (*str == 42 && sing == -1 && doub == -1)
			return (1);
		str++;
	}
	return (0);
}

static void	norminette_smells_like_fish(char **pattern, char**str)
{
	while (**pattern && **str)
	{
		if (**pattern == 42)
		{
			while (**pattern == 42)
				(*pattern)++;
			if (!strchr(*pattern, 42))
				break ;
			while (**str && **pattern != **str)
				(*str)++;
		}
		else if (**pattern != **str)
			break ;
		else
		{
			if (**pattern)
				(*pattern)++;
			if (**str)
				(*str)++;
		}
	}
}

/** @brief find matches for the wildcard characters
 * @return -1 if wildcard is matched to a period,
	0 if a match has been found
	or a number other than 0 or -1 if there's a discrepancy
*/
int	match(char *pattern, char *str)
{
	if (*pattern == 42 && *str == 46)
		return (-1);
	norminette_smells_like_fish(&pattern, &str);
	while (*pattern == 42)
		pattern++;
	if (ft_strlen(pattern) > ft_strlen(str))
		return (1);
	while (*str)
		str++;
	str -= ft_strlen(pattern);
	while (*pattern && *str && *pattern == *str)
	{
		pattern++;
		str++;
	}
	return (*pattern - *str);
}
