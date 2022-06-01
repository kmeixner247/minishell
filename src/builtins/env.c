/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/01 09:45:11 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * @brief env builtin - prints out content
 * of env variable
 */
int	ft_env(t_shell *shell, t_token *token)
{
	t_env	*tempenv;

	if (token->args->next)
		ft_error_msg(shell, ERR_ENV_ARG, 1);
	tempenv = shell->env;
	while (tempenv)
	{
		if (check_char('=', tempenv->var))
			ft_putendl_fd(tempenv->var, 1);
		tempenv = tempenv->next;
	}
	return (0);
}
