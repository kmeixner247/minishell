/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:58:46 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/30 15:22:05 by jsubel           ###   ########.fr       */
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
