/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:27:56 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/03 14:06:40 by jsubel           ###   ########.fr       */
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

/** @brief initialize env linked list from char **envp, increase SHLVL by 1
 * for each time minishell is opened */
t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*tmp;
	int		shell_level;
	char	*tmp_itoa;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		if (!(ft_strncmp("SHLVL=", envp[i], 6)))
		{
			shell_level = ft_atoi(ft_strchr(envp[i], '=') + 1) + 1;
			tmp_itoa = ft_strjoin3("SHLVL=", ft_itoa(shell_level));
			tmp = new_env(tmp_itoa);
		}
		else
			tmp = new_env(envp[i]);
		env_addback(&env, tmp);
		i++;
	}
	return (env);
}

/** @brief turn back env linked list into char ** */
char	**get_env(t_env *env)
{
	char	**envv;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	envv = ft_calloc(sizeof(char *), i + 1);
	envv[i] = NULL;
	i = 0;
	tmp = env;
	while (tmp)
	{
		envv[i] = tmp->var;
		tmp = tmp->next;
		i++;
	}
	return (envv);
}

int	free_env(t_env *env)
{
	t_env	*tmpenv;

	while (env)
	{
		tmpenv = env;
		env = env->next;
		free(tmpenv->var);
		free(tmpenv);
	}
	return (0);
}
