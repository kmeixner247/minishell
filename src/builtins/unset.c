/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:30:02 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 20:02:46 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	env_delfirst(t_env **env)
{
	t_env	*tempenv;

	tempenv = *env;
	*env = tempenv->next;
	free(tempenv->var);
	free(tempenv);
}

static void	env_delnext(t_env **env)
{
	t_env	*tempenv;

	tempenv = (*env)->next;
	(*env)->next = (*env)->next->next;
	free(tempenv->var);
	free(tempenv);
}

static	void	find_and_unset(char *arg, t_env **env, int varlen)
{
	t_env	*tempenv;

	tempenv = *env;
	if (!ft_strncmp(arg, tempenv->var, varlen) && \
		(tempenv->var[varlen] == 61 || !tempenv->var[varlen]))
		env_delfirst(env);
	else
	{
		while (tempenv->next)
		{
			if (!ft_strncmp(arg, tempenv->next->var, varlen) && \
				(tempenv->next->var[varlen] == 61 || \
				!tempenv->next->var[varlen]))
				break ;
			tempenv = tempenv->next;
		}
		if (tempenv->next)
			env_delnext(&tempenv);
	}
}

int	ft_unset(t_env **env, char **args)
{
	int		i;
	int		status;
	t_env	*tempenv;

	status = 0;
	i = 1;
	while (args[i])
	{
		tempenv = *env;
		if (!is_valid_varname(args[i]))
		{
			printf("Bad variable name! BAD VARIABLE NAME!!\n");
			status = 1;
		}
		else
			find_and_unset(args[i], env, ft_strlen(args[i]));
		i++;
	}
	return (status);
}
