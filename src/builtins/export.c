/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:29:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 17:52:55 by kmeixner         ###   ########.fr       */
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
	{
		ft_putchar_fd('\n', 1);
		return ;
	}	
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
		if (ft_strcmp(lowest, env->var) > 0 && \
			ft_strcmp(previous, env->var) < 0)
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

//still need to protect variable names
//can't start with number
//only alphanumerical
//dirty exceptions?
int	is_valid_varname(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != 95)
		return (1);
	arg++;
	while (*arg && (isalnum(*arg) || *arg == 95))
		arg++;
	if (*arg)
		return (1);
	else
		return (0);
}

char	*get_varname(char *arg)
{
	int		i;
	char	*ret;

	i = 0;
	while (arg[i] && arg[i] != 61)
		i++;
	ret = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(ret, arg, i + 1);
	return (ret);
}

void	add_or_update_var(char *arg, t_env *env)
{
	char	*tempstr;
	t_env	*newenv;

	tempstr = get_varname(arg);
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

	tempenv = *env;
	if (!args[1])
		print_alphabetical(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!isvalid_varname(args[i]))
			{
				// ft_error_msg();
				printf("Bad variable name! Bad variable name!\n");
				status = 1;
			}
			add_or_update_var(args[i], env);
			i++;
		}
	}
	return (status);
}
