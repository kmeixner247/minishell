/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:24:27 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/17 16:17:01 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_nbr_args(char **args)
{
	int	nbr;

	nbr = 0;
	while (args[nbr])
		nbr++;
	return (nbr);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag_n;

	i = 0;
	flag_n = 0;
	if (ft_nbr_args(args) > 1)
	{
		if (ft_strcmp(args[0], "-n") == 0)
		{
			flag_n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (flag_n == 0)
		write(1, "\n", 1);
	return (1);
}
