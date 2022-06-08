/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_logicals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:27:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/08 13:04:05 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_logical	*new_logical(char *str)
{
	t_logical	*new;
	int			size;

	cut_spaces(&str);
	new = ft_calloc(1, sizeof(t_logical));
	if (!new)
		return (NULL);
	new->operator = set_operator(str);
	if ((*str == 38 && *(str + 1) == 38) || (*str == 124 && *(str + 1) == 124))
		str += 2;
	while (*str == 32)
		str++;
	if (has_logical(str))
		size = find_size(str);
	else
		size = ft_strlen(str);
	new->parentheses = set_parentheses_flag(&str, &size);
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

char	*has_logical(char *str)
{
	int	sing;
	int	doub;

	sing = -1;
	doub = -1;
	while (*str)
	{
		if (*str == 40 && sing == -1 && doub == -1)
			str += find_closing_parenthesis(str);
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
