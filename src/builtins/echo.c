/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:24:27 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 08:49:20 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_nbr_args(t_args *args)
{
	int	nbr;

	nbr = 0;
	while (args)
	{
		args = args->next;
		nbr++;
	}
	return (nbr);
}

int	ft_echo(t_args *args)
{
	int	i;
	int	flag_n;

	i = 0;
	flag_n = 0;
	if (ft_nbr_args(args) > 1)
	{
		args = args->next;
		if (ft_strcmp(args->arg, "-n") == 0)
		{
			flag_n = 1;
			args = args->next;
		}
		while (args)
		{
			ft_putstr_fd(args->arg, 1);
			if (args->next && args->arg)
				write(1, " ", 1);
			args = args->next;
		}
	}
	if (flag_n == 0)
		write(1, "\n", 1);
	return (1);
}
