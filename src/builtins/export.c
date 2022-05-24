/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:29:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/24 15:03:46 by kmeixner         ###   ########.fr       */
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
			(tempenv->var[ft_strlen(arg)] == 61 || \
			!tempenv->var[ft_strlen(arg)]))
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

static int	search_env(t_shell *shell, char **args)
{
	int		i;
	int		status;
	char	*tempstr;

	i = 1;
	status = 0;
	while (args[i])
	{
		tempstr = get_varname(args[i]);
		if (!is_valid_varname(tempstr))
		{
			printf("BAD\n");
			status = 1;
		}
		else
			add_or_update_var(args[i], &(shell->env));
		free(tempstr);
		i++;
	}
	return (status);
}

int	ft_export(t_shell *shell)
{
	int		i;
	int		status;
	char	*tempstr;
	char	**args;

	status = 0;
	args = get_args(shell->token->args);
	if (!args[1])
		print_alphabetical(shell->env);
	else
		status = search_env(shell, args);
	free(args);
	return (status);
}
