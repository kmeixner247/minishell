/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_accountant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:20:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/03 20:03:25 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//writes *envvar into *ret, while enclosing ' into "" and vice versa
//also encloses $, <, > and | in ''
static void	write_var(char *ret, char *envvar)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envvar[i])
	{
		if (envvar[i] == 34 || envvar[i] == 39 || envvar[i] == 36 || \
			envvar[i] == 124 || envvar[i] == 60 || envvar[i] == 62)
		{
			if (envvar[i] == 34 || envvar[i] == 36 || envvar[i] == 124 || \
				envvar[i] == 60 || envvar[i] == 62)
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
static char	*assemble_var(char *envvar)
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
		if (envvar[i] == 34 || envvar[i] == 39 || envvar[i] == 36)
			j += 2;
		i++;
		j++;
	}
	ret = ft_calloc(sizeof(char), j + 1);
	write_var(ret, envvar);
	return (ret);
}

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
		if (str[pos] == 36 && sing == -1 && (isalnum(str[pos + 1]) || \
			str[pos + 1] == 95 || str[pos + 1] == 63 || \
			(str[pos + 1] == 34 && doub == -1) || str[pos + 1] == 39))
			break ;
		pos++;
	}
	*doubflag = doub;
	if (str[pos])
		return (pos);
	else
		return (-1);
}

//Finds and returns the value of the variable $str in envp
//Returns an allocated empty string if the variable doesn't exist
//Also prepares quotes to be handled correctly by the quote remover
char	*get_env_value(char *str, char **envp, int doubflag)
{
	int		size;
	int		i;
	char	*ret;
	char	*tmp;

	if (!str || !*str)
		return (ft_strdup(""));
	i = 0;
	size = 0;
	tmp = ft_strjoin(str, "=");
	while (envp[i] && ft_strncmp(tmp, envp[i], ft_strlen(tmp)))
		i++;
	free(tmp);
	if (!envp[i])
		ret = ft_strdup("");
	else
	{
		ret = assemble_var(envp[i]);
		if (doubflag == 1)
			ret = ft_strjoin3("\"", ft_strjoin2(ret, "\""));
	}
	return (ret);
}

//returns the valid environmental variable name, starting at *str
char	*find_env_varname(char *str, char **envp)
{
	int		size;
	char	*ret;

	size = 0;
	if (ft_isdigit(*str))
		size = 1;
	else
	{
		while (isalnum(str[size]) || str[size] == 95)
			size++;
	}
	ret = ft_calloc(sizeof(char), size + 1);
	ft_strlcpy(ret, str, size + 1);
	return (ret);
}
