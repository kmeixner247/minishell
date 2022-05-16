/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 09:02:54 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var)
{
	t_env *newenv;

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
	int	i;
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

void env(t_env *env)
{
	t_env	*tempenv;

	tempenv = env;
	while (tempenv)
	{
		printf("here: %s\n", tempenv->var);
		tempenv = tempenv->next;
	}
}

void	export(t_env **env, char**args)
{
	t_env	*newenv;
	int		i;

	i = 1;
	while (args[i])
	{
		newenv = new_env(args[i]);
		env_addback(env, newenv);
	}	
}

void	unset(t_env **env, char **args)
{
	t_env	*tempenv;
	t_env	*next;
	char	*tempstr;
	int		i;

	i = 1;
	while (args[i])
	{
		tempenv = *env;
		tempstr = ft_strjoin(args[i], "=");
		if (ft_strncmp(tempstr, tempenv->var, ft_strlen(tempstr)))
		{
			*env = tempenv->next;
			free(tempenv->var);
			free(tempenv);
		}
		else
		{
			while (tempenv->next && ft_strncmp(tempstr, tempenv->next->var, ft_strlen(tempstr)))
				tempenv = tempenv->next;
			if (tempenv)
			{
				tempenv->next = tempenv->next->next;
				free(tempenv->next->var);
				free(tempenv->next);
			}
		}
		free(tempstr);
		i++;
	}
}