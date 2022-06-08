/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prechecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:30:07 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/07 23:29:08 by kmeixner         ###   ########.fr       */
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
		if (*str == 124 && *(str + 1) != 124)
		{
			str++;
			while (*str == 32)
				str++;
			if (!*str || *str == 124)
				return (1);
		}
		str += quote_skipper(str);
		if (*str)
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
			if (check_char(*str, "<>|") || (*str == 38 && *(str + 1) == 38))
				return (1);
		}
		str += quote_skipper(str);
		if (*str)
			str++;
	}
	return (0);
}

int	justspaces(char *str)
{
	while (*str == 32)
		str++;
	if (!*str)
		return (1);
	else
		return (0);
}

int	checklogicals(char *str)
{
	while (*str)
	{
		if ((*str == 124 && *(str + 1) == 124) || \
			(*str == 38 && *(str + 1) == 38))
		{
			str += 2;
			while (*str == 32)
				str++;
			if (check_char(*str, "<>|") || (*str == 38 && *(str + 1) == 38))
				return (1);
		}
		str += quote_skipper(str);
		if (*str)
			str++;
	}
	return (0);
}

int	check_empty_parentheses(char *str)
{
	if (*str == 40)
		str++;
	while (*str == 32)
		str++;
	if (*str == 41)
		return (1);
	return (0);
}

int	check_opening_parentheses(char *str)
{
	int	start;
	int	i;

	i = 0;
	start = 1;
	while (*str)
	{
		if (*str == 40 && (start == 0 || check_empty_parentheses(str)))
			return (1);
		if ((*str == 38 || *str == 124) && *str == *(str + 1))
		{
			str++;
			start = 1;
		}
		else if (*str != 32 && *str != 40)
			start = 0;
		str += quote_skipper(str);
		if (*str)
			str++;
	}
	return (0);
}

int	check_closing_parentheses(char *str)
{
	while (*str)
	{
		if (*str == 41)
		{
			str++;
			while (*str == 32)
				str++;
			if (!(!*str || *str == 41 || *str == 38 && *(str + 1) == 38 \
				|| *str == 124 && *(str + 1) == 124))
				return (1);
		}
		str += quote_skipper(str);
		if (*str && *str != 41)
			str++;
	}
	return (0);
}

int	checkparentheses(char *str)
{
	int	level;
	int	i;

	i = 0;
	level = 0;
	while (str[i])
	{
		if (str[i] == 40)
			level++;
		if (str[i] == 41)
			level--;
		i += quote_skipper(str + i);
		if (str[i])
			i++;
	}
	if (level != 0)
		return (1);
	if (check_opening_parentheses(str) || check_closing_parentheses(str))
		return (1);
	return (0);
}

int	prechecks(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (*str == 32)
		str++;
	if (justspaces(str))
		return (-1);
	if (check_openquotes(str))
		ft_error_msg(shell, ERR_UNCLOSED_QUOTES, 258);
	else if (checklogicals(str))
		ft_error_msg(shell, ERR_LOGICS_INPUT, 258);
	else if (*str == 124 || checkpipes(str))
		ft_error_msg(shell, ERR_PIPE_INPUT, 258);
	else if (checkredirs(str))
		ft_error_msg(shell, ERR_REDIR_INPUT, 258);
	else if (checkparentheses(str))
		ft_error_msg(shell, ERR_PARENTH_INPUT, 258);
	else
		return (0);
	return (-1);
}
