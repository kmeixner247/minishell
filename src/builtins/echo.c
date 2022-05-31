/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:24:27 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/31 15:51:19 by kmeixner         ###   ########.fr       */
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

int	ft_echo(t_shell *shell, t_token *token, t_args *args)
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
			ft_putstr_fd(args->arg, token->outfd);
			if (args->next && args->arg)
				write(token->outfd, " ", 1);
			args = args->next;
		}
	}
	if (flag_n == 0)
		write(token->outfd, "\n", 1);
	return (0);
}
