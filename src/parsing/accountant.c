/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accountant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:23:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/15 16:25:56 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the position of the first non-escaped $
//Returns -1 if there is none
static int	find_cash(char *str, int *doubflag)
{
	int	sing;
	int	doub;
	int	pos;

	sing = -1;
	doub = -1;
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == 39 && doub == -1) //'
			sing *= -1;
		if (str[pos] == 34 && sing == -1) //"
			doub *= -1;
		if (str[pos] == 36 && sing == -1) //$
			break ;
		pos++;
	}
	*doubflag = doub;
	if (str[pos])
		return (pos);
	else
		return (-1);
}

static void	write_var(char *ret, char *envvar)
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
static char	*find_env_var(char *str, char **envp, int doubflag)
{
	int		size;
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	size = 0;
	while (!check_char(str[size], "\'\" <>|")) //finding size of variable name
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

//Exchanges dollars for real stuff
static char	*currency_exchange(char *str, char **envp)
{
	char	*before;
	char	*replace;
	char	*after;
	char	*result;
	int		doubflag;

	before = str;
	str += find_cash(str, &doubflag);
	*str = 0; //replacing the $ with \0, terminating the before string
	str++;
	replace = find_env_var(str, envp, doubflag);
	while (!check_char(*str, "\'\" <>|"))
		str++;
	after = str;
	result = ft_strjoin2(ft_strjoin(before, replace), after);
	return (result);
}

//handles all the dollars
char	*accountant(char *str, char **envp)
{
	char	*tmp;
	int		doubflag;

	doubflag = -1;
	tmp = str;
	while (find_cash(str, &doubflag) >= 0)
		str = currency_exchange(str, envp);
	if (tmp != str)
		free(tmp);
	return (str);
}

void	meta_accountant(t_token *token, char **envp)
{
	t_args	*args;
	t_redir	*redir;

	while (token)
	{
		args = token->args;
		while (args)
		{
			args->arg = accountant(args->arg, envp);
			args = args->next;
		}
		redir = token->redir;
		while (redir)
		{
			redir->filename = accountant(redir->filename, envp);
			redir = redir->next;
		}
		token = token->next;
	}
}
