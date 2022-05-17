/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:29:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 16:37:10 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_variable(char *str)
{
	int	i;

	ft_putstr_fd("declare -x ", 1);
	i = 0;
	while (str[i] && str[i] != 61)
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	if (!str[i])
		return ;
	ft_putchar_fd(str[i], 1);
	i++;
	ft_putchar_fd('\"', 1);
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putstr_fd("\"\n", 1);
}

char	*next_lowest(t_env *env, char *previous)
{
	char	*lowest;
	char	*temp;

	temp = malloc(sizeof(char));
	temp[0] = 127;
	lowest = temp;
	while (env)
	{
		if (ft_strcmp(lowest, env->var) > 0 && ft_strcmp(previous, env->var) < 0)
			lowest = env->var;
		env = env->next;
	}
	free(temp);
	return (lowest);
}

void	print_alphabetical(t_env *env)
{
	int		n;
	t_env	*tempenv;
	char	*lowest;

	n = 0;
	tempenv = env;
	while (tempenv)
	{
		tempenv = tempenv->next;
		n++;
	}
	lowest = next_lowest(env, "");
	while (n > 0)
	{
		print_variable(lowest);
		lowest = next_lowest(env, lowest);
		n--;
	}
}

//still need to export empty variables
//still need to protect variable names
//can't start with number
//only alphanumerical
//dirty exceptions?

void	export(t_env **env, char**args)
{
	char	*tempstr;
	t_env	*newenv;
	t_env	*tempenv;
	int		i;

	tempenv = *env;
	if (!args[1])
	{
		print_alphabetical(*env);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			tempstr = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			while (tempenv && ft_strncmp(tempstr, tempenv->var, (ft_strlen(tempstr))))
			{
				tempenv = tempenv->next;
			}	
			free(tempstr);
			if (tempenv)
			{
				free(tempenv->var);
				tempenv->var = ft_strdup(args[i]);
			}
			else
			{
				newenv = new_env(args[i]);
				env_addback(env, newenv);
			}
			i++;
		}
	}
}