/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:27:56 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 08:37:57 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_env	*new_env(char *var)
{
	t_env	*newenv;

	newenv = ft_calloc(sizeof(t_env), 1);
	if (!newenv)
		return (NULL);
	newenv->var = ft_strdup(var);
	newenv->next = NULL;
	return (newenv);
}

void	env_addback(t_env **start, t_env *new)
{
	t_env	*temp;

	temp = *start;
	if (!temp)
	{
		*start = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = new_env(envp[i]);
		env_addback(&env, tmp);
		i++;
	}
	return (env);
}
