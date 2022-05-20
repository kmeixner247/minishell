/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accountant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:23:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/20 16:23:46 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//finds the first environmental variable in str (recognized by a non-escaped $)
//replaces the variable with its value while preparing the string for proper
//quote removal and returns the resulting string
char	*currency_exchange(char *str, char **envp)
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
	varname = find_env_varname(str, envp);
	replace = get_env_value(varname, envp, doubflag);
	str += ft_strlen(varname);
	free(varname);
	after = str;
	return (ft_strjoin2(ft_strjoin(before, replace), after));
}

//handles all the dollars
static char	*accountant(char *str, char **envp)
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

//runs the accountant on all filenames and args of each token
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
