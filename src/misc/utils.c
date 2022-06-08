/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:58:39 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/08 12:47:43 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

/**
 * @brief very necessary function. !!!DO NOT TOUCH!!!
 * @param str1 a string
 * @param str2 another string
 */
void	ft_free_chars(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

/** @brief find a certain element within env */
t_env	*ft_find_element(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->var, ft_strlen(str)))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
