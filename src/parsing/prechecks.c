/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prechecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:30:07 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/29 17:03:13 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_openquotes(char *str)
{
	int	sing;
	int	doub;

	sing = -1;
	doub = -1;
	while (*str)
	{
		if (*str == 34 && sing == -1)
			doub *= -1;
		if (*str == 39 && doub == -1)
			sing *= -1;
		str++;
	}
	if (sing == 1 || doub == 1)
		return (1);
	else
		return (0);
}

static int	checkpipes(char *str)
{
	while (*str)
	{
		if (*str == 124)
		{
			str++;
			while (*str == 32)
				str++;
			if (!*str || *str == 124)
				return (1);
		}
		str += quote_skipper(str);
		str++;
	}
	return (0);
}

static int	checkredirs(char *str)
{
	while (*str)
	{
		if (*str == 60 | *str == 62)
		{
			str++;
			if (*str == *(str - 1))
				str++;
			while (*str == 32)
				str++;
			if (check_char(*str, "<>|"))
				return (1);
		}
		str += quote_skipper(str);
		str++;
	}
	return (0);
}

int	prechecks(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (*str == 32)
		str++;
	if (check_openquotes(str))
		ft_error_msg(shell, ERR_UNCLOSED_QUOTES, 1);
	else if (*str == 124 || checkpipes(str))
		ft_error_msg(shell, ERR_PIPE_INPUT, 1);
	else if (checkredirs(str))
		ft_error_msg(shell, ERR_REDIR_INPUT, 1);
	else
		return (0);
	return (-1);
}
