/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:30:02 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/20 16:23:01 by kmeixner         ###   ########.fr       */
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

void	unset(t_env **env, char **args)
{
	t_env	*tempenv;
	t_env	*tempenv2;
	char	*tempstr;
	int		i;

	i = 1;
	while (args[i])
	{
		tempenv = *env;
		tempstr = ft_strjoin(args[i], "=");
		if (!ft_strncmp(tempstr, tempenv->var, ft_strlen(tempstr)))
			env_delfirst(env);
		else
		{
			while (tempenv->next && ft_strncmp(tempstr, \
					tempenv->next->var, ft_strlen(tempstr)))
				tempenv = tempenv->next;
			if (tempenv)
				env_delnext(&tempenv);
		}
		free(tempstr);
		i++;
	}
}
