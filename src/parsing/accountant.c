/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accountant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:23:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 13:22:19 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
