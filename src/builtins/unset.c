/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:30:02 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/01 15:15:34 by kmeixner         ###   ########.fr       */
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

/** @brief walk through each element of env and check if the
 * variable is already set and, if it is, delete the corresponding
 * element from the linked list */
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

/**
 * @brief unset variable from environment by checking if
 * the name is valid and, if it is, then valling a function
 * to find and delete the corresponding element of the linked list */
int	ft_unset(t_shell *shell)
{
	int		i;
	int		status;
	t_env	*tempenv;
	char	**args;

	args = get_args(shell->token->args);
	status = 0;
	i = 1;
	while (args[i])
	{
		tempenv = shell->env;
		if (!is_valid_varname(args[i]))
		{
			ft_error(shell, args[i], ERRNO_UNSET);
			status = 1;
		}
		else
			find_and_unset(args[i], &(shell->env), ft_strlen(args[i]));
		i++;
	}
	free(args);
	return (status);
}
