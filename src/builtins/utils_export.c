/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:00:28 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 19:32:37 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	print_variable(char *str)
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

static char	*next_lowest(t_env *env, char *previous)
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

int	is_valid_varname(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != 95)
		return (0);
	arg++;
	while (*arg && (isalnum(*arg) || *arg == 95))
		arg++;
	if (*arg)
		return (0);
	else
		return (1);
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
