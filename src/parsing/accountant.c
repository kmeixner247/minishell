/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accountant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:23:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/28 11:45:23 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//finds the first environmental variable in str (recognized by a non-escaped $)
//replaces the variable with its value while preparing the string for proper
//quote removal and returns the resulting string
char	*currency_exchange(t_shell *shell, char *str, char **envp)
{
	char	*before;
	char	*replace;
	char	*after;
	int		doubflag;
	char	*varname;

	before = str;
	str += find_cash(str, &doubflag);
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
		replace = get_env_value(varname, envp, doubflag);
		str += ft_strlen(varname);
		free(varname);
	}
	after = str;
	return (ft_strjoin2(ft_strjoin3(before, replace), after));
}

//handles all the dollars
char	*accountant(t_shell *shell, char *str)
{
	char	*tmp;
	int		doubflag;
	char	**envp;

	envp = get_env(shell->env);
	doubflag = -1;
	tmp = str;
	while (find_cash(str, &doubflag) >= 0)
		str = currency_exchange(shell, str, envp);
	if (tmp != str)
		free(tmp);
	return (str);
}

//runs the accountant on all filenames and args of each token
void	meta_accountant(t_shell *shell, t_token *token)
{
	t_args	*tmp;

	tmp = token->args;
	while (tmp)
	{
		tmp->arg = accountant(shell, tmp->arg);
		tmp = tmp->next;
	}
}
