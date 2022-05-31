/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:24:27 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/31 22:14:03 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_echo_isvalidflag(char *str)
{
	if (!str || *str != 45)
		return (0);
	str++;
	while (*str)
	{
		if (*str != 110)
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(t_shell *shell, t_args *args)
{
	int	i;
	int	flag_n;

	i = 0;
	flag_n = 0;
	if (ft_nbr_args(args) > 1)
	{
		args = args->next;
		while (args && ft_echo_isvalidflag(args->arg))
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
	return (0);
}
