/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logicals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:07:10 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/06 18:48:07 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*has_logical(char *str)
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
		if (*str == 38 && sing == -1 && doub == -1 && *(str + 1) == 38)
			return (str);
		if (*str == 124 && sing == -1 && doub == -1 && *(str + 1) == 124)
			return (str);
		str++;
	}
	return (NULL);
}

void	logical_addback(t_logical **start, t_logical *new)
{
	t_logical	*temp;

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

t_logical	*new_logical(char *str)
{
	int			size;
	t_logical	*new;

	new = ft_calloc(1, sizeof(t_logical));
	if (!new)
		return (NULL);
	new->operator = 0;
	if (*str == 38)
	{
		new->operator = 1;
		str += 2;
	}
	else if (*str == 124)
	{
		new->operator = 2;
		str += 2;
	}
	if (has_logical(str))
		size = has_logical(str) - str;
	else
		size = ft_strlen(str);
	new->token = ft_calloc(size + 1, sizeof(char));
	ft_strlcpy(new->token, str, size + 1);
	new->next = NULL;
	return (new);
}

t_logical	*split_by_logicals(char *input)
{
	char		*tmp;
	t_logical	*tmplog;
	t_logical	*start;

	tmplog = NULL;
	start = NULL;
	tmp = input;
	while (tmp)
	{
		tmplog = new_logical(tmp);
		logical_addback(&start, tmplog);
		if (tmplog->operator)
			tmp += 2;
		tmp = has_logical(tmp);
	}
	return (start);
}

void	free_logicals(t_logical *logical)
{
	t_logical	*tmp;

	if (!logical)
		return ;
	while (logical)
	{
		tmp = logical;
		logical = logical->next;
		free(tmp->token);
		free(tmp);
	}
}
