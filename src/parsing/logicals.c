/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logicals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:07:10 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/07 13:52:37 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	find_closing_parenthesis(char *str)
{
	int	i;
	int	level;
	int	sing;
	int	doub;

	i = 0;
	level = 0;
	sing = -1;
	doub = -1;
	while (str[i])
	{
		if (str[i] == 41 && sing == -1 && doub == -1)
		{
			if (level == 1)
				break ;
			else
				level--;
		}
		else if (str[i] == 34 && sing == -1)
			doub *= -1;
		else if (str[i] == 39 && doub == -1)
			sing *= -1;
		else if (str[i] == 40 && doub == -1 && sing == -1)
			level++;
		i++;
	}
	return (i);
}

char	*has_logical(char *str)
{
	int	sing;
	int	doub;
	int	paren;

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

void	cut_spaces(char **str)
{
	int	i;

	i = 0;
	while (**str == 32)
		(*str)++;
	while ((*str)[i])
		i++;
	if (i > 0)
		i--;
	while (i > 0 && (*str)[i] == 32)
		i--;
	(*str)[i + 1] = 0;
}

int	find_size(char *str)
{
	char	*end;
	int		i;

	if (!str)
		return (0);
	end = has_logical(str);
	if (end > str)
		end--;
	while (end > str && *end == 32)
		end--;
	if (end != str)
		end++;
	return (end - str);
}

// t_logical	*new_logical(char *str)
// {
// 	int			size;
// 	t_logical	*new;

// 	cut_spaces(&str);
// 	new = ft_calloc(1, sizeof(t_logical));
// 	if (!new)
// 		return (NULL);
// 	new->operator = 0;
// 	if (*str == 38)
// 	{
// 		new->operator = 1;
// 		str += 2;
// 	}
// 	else if (*str == 124)
// 	{
// 		new->operator = 2;
// 		str += 2;
// 	}
// 	if (has_logical(str))
// 		size = find_size(str);
// 	else
// 		size = ft_strlen(str);
// 	new->parentheses = 0;
// 	if (*str == 40)
// 	{
// 		new->parentheses = 1;
// 		str++;
// 		size -= 2;
// 	}
// 	new->token = ft_calloc(size + 1, sizeof(char));
// 	ft_strlcpy(new->token, str, size + 1);
// 	new->next = NULL;
// 	return (new);
// }

t_logical	*new_logical(char *str)
{
	t_logical	*new;
	int			size;

	cut_spaces(&str);
	new = ft_calloc(1, sizeof(t_logical));
	if (!new)
		return (NULL);
	new->operator = 0;
	if (*str == 38 && *(str + 1) == 38)
		new->operator = 1;
	if (*str == 124 && *(str + 1) == 124)
		new->operator = 2;
	if ((*str == 38 && *(str + 1) == 38) || (*str == 124 && *(str + 1) == 124))
		str += 2;
	while (*str == 32)
		str++;
	if (has_logical(str))
		size = find_size(str);
	else
		size = ft_strlen(str);
	new->parentheses = 0;
	if (*str == 40)
	{
		new->parentheses = 1;
		str++;
		size -= 2;
	}
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
