/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:04:21 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/03 18:43:31 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	find_cash_hd(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && !(str[pos] == 36 && \
		(isalnum(str[pos + 1]) || str[pos + 1] == 63 || str[pos + 1] == 95)))
		pos++;
	if (str[pos])
		return (pos);
	else
		return (-1);
}

static char	*get_env_value_hd(char *str, char **envp)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strjoin(str, "=");
	while (envp[i] && ft_strncmp(tmp, envp[i], ft_strlen(tmp)))
		i++;
	free(tmp);
	if (!envp[i])
		return (ft_strdup(""));
	else
	{
		while (envp[i][j] != 61)
			j++;
		j++;
		return (ft_strdup(envp[i] + j));
	}
}

static char	*currency_exchange_hd(t_shell *shell, char *str, char **envp)
{
	char	*before;
	char	*replace;
	char	*after;
	char	*varname;

	before = str;
	str += find_cash_hd(str);
	*str = 0;
	str++;
	if (*str == 63)
	{
		replace = ft_strdup(ft_itoa(shell->lastreturn));
		str++;
	}
	else
	{
		varname = find_env_varname(str, envp);
		replace = get_env_value_hd(varname, envp);
		str += ft_strlen(varname);
		free(varname);
	}
	after = str;
	return (ft_strjoin2(ft_strjoin3(before, replace), after));
}

//this accountant is a simplified version of the main one, as it
//doesn't have to handle single quotes
char	*accountant_hd(t_shell *shell, char *str)
{
	char	*tmp;
	char	**envp;

	envp = get_env(shell->env);
	tmp = str;
	while (find_cash_hd(str) >= 0)
		str = currency_exchange_hd(shell, str, envp);
	if (tmp != str)
		free(tmp);
	free(envp);
	return (str);
}

void	hd_newline(int sig)
{
	printf("\n");
}
