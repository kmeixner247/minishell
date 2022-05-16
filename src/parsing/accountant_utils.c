/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accountant_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:20:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 14:39:35 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
//Returns the position of the first non-escaped $
//Returns -1 if there is none
int	find_cash(char *str, int *doubflag)
{
	int	sing;
	int	doub;
	int	pos;

	sing = -1;
	doub = -1;
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == 39 && doub == -1)
			sing *= -1;
		if (str[pos] == 34 && sing == -1)
			doub *= -1;
		if (str[pos] == 36 && sing == -1)
			break ;
		pos++;
	}
	*doubflag = doub;
	if (str[pos])
		return (pos);
	else
		return (-1);
}

//writes *envvar into *ret, while enclosing ' into "" and vice versa
void	write_var(char *ret, char *envvar)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envvar[i])
	{
		if (envvar[i] == 34 || envvar[i] == 39)
		{
			if (envvar[i] == 34)
				ret[j] = 39;
			else if (envvar[i] == 39)
				ret[j] = 34;
			ret[j + 1] = envvar[i];
			ret[j + 2] = ret[j];
			j += 2;
		}
		else
			ret[j] = envvar[i];
		i++;
		j++;
	}
}

//skips until after the = of the passed envvar and creates 
//and returns a new string with the value
char	*assemble_var(char *envvar)
{
	int		i;
	int		j;
	char	*ret;

	while (*envvar != 61)
		envvar++;
	envvar++;
	i = 0;
	j = 0;
	while (envvar[i])
	{
		if (envvar[i] == 34 || envvar[i] == 39)
			j += 2;
		i++;
		j++;
	}
	ret = ft_calloc(sizeof(char), j + 1);
	write_var(ret, envvar);
	return (ret);
}

//Finds and returns the value of the variable $str in envp
//Returns an allocated empty string if the variable doesn't exist
//Also prepares quotes to be handled correctly by the quote remover
char	*find_env_var(char *str, char **envp, int doubflag)
{
	int		size;
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	size = 0;
	while (!check_char(str[size], "\'\" <>|"))
		size++;
	tmp = ft_calloc(sizeof(char), size + 2);
	ft_strlcpy(tmp, str, size + 1);
	tmp = ft_strjoin2(tmp, "=");
	while (envp[i] && ft_strncmp(tmp, envp[i], size + 1))
		i++;
	if (!envp[i])
		ret = ft_calloc(sizeof(char), 1);
	else
	{
		ret = assemble_var(envp[i]);
		if (doubflag == 1)
			ret = ft_strjoin3("\"", ft_strjoin2(ret, "\""));
	}
	free(tmp);
	return (ret);
}

//finds the first environmental variable in str (recognized by a non-escaped $)
//replaces the variable with its value while preparing the string for proper
//quote removal and returns the resulting string
char	*currency_exchange(char *str, char **envp)
{
	char	*before;
	char	*replace;
	char	*after;
	char	*result;
	int		doubflag;

	before = str;
	str += find_cash(str, &doubflag);
	*str = 0;
	str++;
	replace = find_env_var(str, envp, doubflag);
	while (!check_char(*str, "\'\" <>|"))
		str++;
	after = str;
	result = ft_strjoin2(ft_strjoin(before, replace), after);
	return (result);
}
