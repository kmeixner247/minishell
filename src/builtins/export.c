/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:29:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 19:46:10 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	add_or_update_var(char *arg, t_env **env)
{
	t_env	*newenv;
	t_env	*tempenv;

	tempenv = *env;
	while (tempenv)
	{
		if (!ft_strncmp(arg, tempenv->var, ft_strlen(arg)) && \
			(arg[ft_strlen(arg)] == 61 || !arg[ft_strlen(arg)]))
			break ;
		tempenv = tempenv->next;
	}
	if (tempenv)
	{
		if (check_char('=', arg))
		{
			free(tempenv->var);
			tempenv->var = ft_strdup(arg);
		}
	}
	else
	{
		newenv = new_env(arg);
		env_addback(env, newenv);
	}
}

int	ft_export(t_env **env, char**args)
{
	int		i;
	int		status;
	char	*tempstr;

	if (!args[1])
		print_alphabetical(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			tempstr = get_varname(args[i]);
			if (!is_valid_varname(tempstr))
			{
				printf("Bad variable name! Bad variable name!\n");
				status = 1;
			}
			else
				add_or_update_var(args[i], env);
			free(tempstr);
			i++;
		}
	}
	return (status);
}
