/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/31 22:14:39 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
