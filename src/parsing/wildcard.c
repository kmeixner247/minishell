/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:55:03 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/28 12:18:43 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

static int	match(char *arg1, char *arg2)
{
	if (*arg1 == 42 && *arg2 == 46)
		return (-1);
	while (*arg1 && *arg2)
	{
		if (*arg1 == 42)
		{
			arg1++;
			while (*arg2 && *arg1 != *arg2)
				arg2++;
		}
		else if (*arg1 != *arg2)
			break ;
		else
		{
			if (*arg1)
				arg1++;
			if (*arg2)
				arg2++;
		}
	}
	while (*arg1 == 42)
		arg1++;
	return (*arg1 - *arg2);
}

t_args	*args_wildcard(t_args *args)
{
	t_args			*start;
	DIR				*dir;
	struct dirent	*dirent;
	t_args			*new;

	start = new_args();
	start->arg = strdup(args->arg);
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent)
	{
		if (!match(start->arg, dirent->d_name))
		{
			new = new_args();
			new->arg = ft_strdup(dirent->d_name);
			args_addback(&start, new);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	if (start->next)
		args_delfirst(&start);
	free(args->arg);
	free(args);
	return (start);
}

void	meta_args_wildcard(t_token *token)
{
	t_args	*tmp;
	t_args	*previous;
	t_args	*next;

	previous = NULL;
	next = token->args->next;
	tmp = token->args;
	while (tmp)
	{
		next = tmp->next;
		if (haswildcard(tmp->arg))
		{
			tmp = args_wildcard(tmp);
			if (previous)
				previous->next = tmp;
			if (next)
				args_addback(&tmp, next);
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

int	redir_wildcard(t_redir *redir)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*strmatch;

	if (!haswildcard(redir->filename))
		return (0);
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent && match(redir->filename, dirent->d_name))
		dirent = readdir(dir);
	if (!dirent)
	{
		closedir(dir);
		return (0);
	}
	strmatch = strdup(dirent->d_name);
	dirent = readdir(dir);
	while (dirent && match(redir->filename, dirent->d_name))
		dirent = readdir(dir);
	if (dirent)
	{
		free(strmatch);
		closedir(dir);
		printf("Ambiguous redirect\n");
		return (1);
	}
	free(redir->filename);
	redir->filename = strmatch;
	closedir(dir);
	return (0);
}
