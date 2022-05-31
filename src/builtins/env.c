/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/31 16:00:58 by kmeixner         ###   ########.fr       */
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
			ft_putendl_fd(tempenv->var, token->outfd);
		tempenv = tempenv->next;
	}
	return (0);
}
