/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 10:56:56 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/28 20:22:16 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	quotecount(char *str)
{
	int	sing;
	int	doub;
	int	count;

	sing = -1;
	doub = -1;
	count = 0;
	while (*str)
	{
		if (*str == 34 && sing == -1)
		{
			doub *= -1;
			count++;
		}
		if (*str == 39 && doub == -1)
		{
			sing *= -1;
			count++;
		}
		str++;
	}
	return (count);
}

static void	cutquotes(char *src, char *dest)
{
	int	sing;
	int	doub;

	sing = -1;
	doub = -1;
	while (*src)
	{
		if (*src == 34 && sing == -1)
		{
			doub *= -1;
			src++;
		}
		else if (*src == 39 && doub == -1)
		{
			sing *= -1;
			src++;
		}
		else
		{
			*dest = *src;
			src++;
			dest++;
		}
	}
}

char	*replace_string(char *str)
{
	char	*ret;

	if (!str)
		return (NULL);
	ret = ft_calloc(sizeof(char), ft_strlen(str) - quotecount(str) + 1);
	cutquotes(str, ret);
	free(str);
	return (ret);
}

void	quote_handler(t_token *token)
{
	t_args	*args;

	args = token->args;
	while (args)
	{
		args->arg = replace_string(args->arg);
		args = args->next;
	}
}

//Checks if the first char is ' or "
//Returns the number of chars to skip past the closing quotes if yes
//Returns 0 if no
int	quote_skipper(char *str)
{
	int		i;
	char	c;

	c = *str;
	if (c != 34 && c != 39)
		return (0);
	i = 1;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
