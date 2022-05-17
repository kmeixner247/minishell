/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:58:39 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 16:09:11 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//Returns 1 if c appears in str, 0 if not
//Returns 1 if c is 0
int	check_char(unsigned char c, const char *str)
{
	if (!c)
		return (1);
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}
