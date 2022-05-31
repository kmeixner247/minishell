/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:55:03 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/31 20:03:02 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"



/**
 * @brief make a new linked list of arguments with the expansion of wildcards
 * @arg args argument list before expansion
 * @param dir structure of open directory
 * @param dirent struct containing the info from the opened directory
 * @param start duplicated argument list with expanded wildcards
 * @return list of arguments with expanded wildcards
 */
t_args	*args_wildcard(t_args *args)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_args			*new;
	t_args			*start;

	start = new_args();
	start->arg = strdup(args->arg);
	new = NULL;
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent)
	{
		if (!match((args)->arg, dirent->d_name))
		{
			new = new_args();
			new->arg = ft_strdup(dirent->d_name);
			args_addback(&start, new);
		}
		dirent = readdir(dir);
	}
	if (new)
		args_delfirst(&start);
	closedir(dir);
	ft_important_function(args);
	return (start);
}

/**
 * @brief expand token with wildcard to all possibilities
 * @arg token token containing wildcards
 * @param arg_ptrs pointers to different t_arg structs
 */
void	meta_args_wildcard(t_token *token)
{
	t_args	*tmp;
	t_args	*next;
	t_args	*previous;

	previous = NULL;
	tmp = token->args;
	next = tmp->next;
	while (tmp)
	{
		next = tmp->next;
		if (haswildcard(tmp->arg))
		{
			tmp = args_wildcard(tmp);
			if (previous)
				previous->next = tmp;
			else
				token->args = tmp;
			if (next)
				args_addback(&token->args, next);
			while (tmp && tmp->next != next)
				tmp = tmp->next;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

static int	ft_ret_dirent(t_shell *shell, t_redir *redir, char *str, DIR *dir)
{
	free(str);
	closedir(dir);
	ft_error(shell, redir->filename, ERRNO_AMBIG);
	return (1);
}

int	redir_wildcard(t_shell *shell, t_redir *redir)
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
		return (ft_ret_dirent(shell, redir, strmatch, dir));
	free(redir->filename);
	redir->filename = strmatch;
	closedir(dir);
	return (0);
}
