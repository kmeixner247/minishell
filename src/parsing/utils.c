/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:58:39 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/15 14:00:18 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns 1 if c appears in str, 0 if not
//Returns 1 if c is 0
int	check_char(unsigned char c, const char *str)
{
	if (!c)
		return (1);
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

t_token	*new_token(void)
{
	t_token	*newtoken;

	newtoken = ft_calloc(sizeof(t_token), 1);
	if (!newtoken)
		return (NULL);
	newtoken->args = NULL;
	newtoken->redir = NULL;
	newtoken->next = NULL;
	return (newtoken);
}

void	token_addback(t_token **start, t_token *new)
{
	t_token	*temp;

	temp = *start;
	if (!temp)
	{
		*start = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_redir	*new_redir(void)
{
	t_redir	*newredir;

	newredir = ft_calloc(sizeof(t_redir), 1);
	if (!newredir)
		return (NULL);
	newredir->id = 0;
	newredir->filename = NULL;
	newredir->next = (NULL);
	return (newredir);
}

void	redir_addback(t_redir **start, t_redir *new)
{
	t_redir	*temp;

	temp = *start;
	if (!temp)
	{
		*start = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_args	*new_args(void)
{
	t_args	*newargs;

	newargs = ft_calloc(sizeof(t_args), 1);
	if (!newargs)
		return (NULL);
	newargs->arg = NULL;
	newargs->next = NULL;
	return (newargs);
}

void	args_addback(t_args **start, t_args *new)
{
	t_args	*temp;

	temp = *start;
	if (!temp)
	{
		*start = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
