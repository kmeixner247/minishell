/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:29:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 18:06:21 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	add_or_update_var(char *arg, t_env *env)
{
	char	*tempstr;
	t_env	*newenv;

	while (env)
	{
		if (!ft_strncmp(tempstr, env->var, ft_strlen(tempstr)) && \
			(arg[ft_strlen(tempstr)] == 61 || !arg[ft_strlen(tempstr)]))
			break ;
		env = env->next;
	}
	free(tempstr);
	if (env)
	{
		if (check_char('=', arg))
		{
			free(env->var);
			env->var = ft_strdup(arg);
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
	t_env	*tempenv;
	int		i;
	int		status;
	char	*tempstr;

	tempenv = *env;
	if (!args[1])
		print_alphabetical(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			tempstr = get_varname(args[i]);
			if (!isvalid_varname(tempstr))
			{
				// ft_error_msg();
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
