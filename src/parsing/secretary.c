/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secretary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:37:40 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 13:16:16 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	identify_redir(char *str)
{
	if (*str == 60)
	{
		if (*(str + 1) == 60)
			return (2);
		else
			return (1);
	}
	else if (*str == 62)
	{
		if (*(str + 1) == 62)
			return (4);
		else
			return (3);
	}
	return (0);
}

static t_redir	*redirect_handler(char **strptr)
{
	t_redir	*redir;
	int		i;
	char	*str;

	str = *strptr;
	redir = new_redir();
	redir->id = identify_redir(str);
	str += (2 - redir->id % 2);
	while (*str == 32)
		str++;
	i = 0;
	while (str[i] && !check_char(str[i], "<> "))
	{
		i += quote_skipper(str + i);
		i++;
	}
	redir->filename = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(redir->filename, str, i + 1);
	str += i;
	*strptr = str;
	return (redir);
}

static t_args	*args_handler(char **strptr)
{
	char	*str;
	t_args	*args;
	int		i;

	str = *strptr;
	args = new_args();
	i = 0;
	while (str[i] && !check_char(str[i], "<> "))
	{
		i += quote_skipper(str + i);
		i++;
	}
	args->arg = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(args->arg, str, i + 1);
	str += i;
	*strptr = str;
	return (args);
}

static t_token	*get_token(char *str)
{
	t_token	*token;
	t_redir	*redir;
	t_args	*args;

	token = new_token();
	while (*str)
	{
		while (*str == 32)
			str++;
		if (*str == 60 || *str == 62)
		{
			redir = redirect_handler(&str);
			redir_addback(&(token)->redir, redir);
		}
		else if (*str)
		{
			args = args_handler(&str);
			args_addback(&(token)->args, args);
		}
	}
	return (token);
}

t_token	*secretary(char **arr)
{
	int		i;
	t_token	*token;
	t_token	*newtoken;

	token = NULL;
	i = 0;
	while (arr[i])
	{
		newtoken = get_token(arr[i]);
		token_addback(&token, newtoken);
		i++;
	}
	free(arr);
	return (token);
}
