/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:29:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/07 11:32:38 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * @brief check if variable exists with the given name inside env
 * and if it does, replace its value. If not, add a new var to
 * the end of env
 * */
void	add_or_update_var(char *arg, char *name, t_env **env)
{
	t_env	*newenv;
	t_env	*tempenv;

	tempenv = *env;
	while (tempenv)
	{
		if (!ft_strncmp(arg, tempenv->var, ft_strlen(name)) && \
			(tempenv->var[ft_strlen(name)] == 61 || \
			!tempenv->var[ft_strlen(name)]))
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

/**
 * @brief search through env variables to check
 * if exported variable has a valid name and, if it does,
 * add or update the corresponding variable
 * */
static int	search_env(t_shell *shell, char **args)
{
	int		i;
	int		status;
	char	*tempstr;
	char	*errstr;
	i = 1;
	status = 0;
	while (args[i])
	{
		tempstr = get_varname(args[i]);
		if (!is_valid_varname(tempstr))
		{
			if (tempstr[0] == '-')
			{
				errstr = ft_strdup("export: ");
				errstr = ft_strjoin3(errstr, ft_substr(tempstr, 0, 2));
				errstr = ft_strjoin2(errstr, ": ");
				errstr = ft_strjoin2(errstr, ERR_INVAL_OPT);
				ft_error_msg(shell, errstr, ERRNO_INVAL_OPT);
				free(errstr);
			}
			else
				ft_error(shell, args[i], ERRNO_EXPORT);
			status = 1;
		}
		else
			add_or_update_var(args[i], tempstr, &(shell->env));
		free(tempstr);
		i++;
	}
	return (status);
}

/**
 * @brief list or add new environmental variables for use in subprocesses
 * of the shell
 * @param status return 1 if error occured or 0 if everthing went well
 */
int	ft_export(t_shell *shell, t_token *token)
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
