/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:55:03 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/30 15:22:00 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/** @brief find matches for the wildcard characters
 * @return -1 if wildcard is matched to a period,
	0 if a match has been found
	or a number other than 0 or -1 if there's a discrepancy
*/
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
