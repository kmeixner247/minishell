/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/29 19:16:18 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_shell *shell, t_args *args, t_env *env)
{
	t_env	*tempenv;

	if (args->next)
		ft_error_msg(shell, ERR_ENV_ARG, 1);
	tempenv = env;
	while (tempenv)
	{
		if (check_char('=', tempenv->var))
			printf("%s\n", tempenv->var);
		tempenv = tempenv->next;
	}
	return (0);
}
