/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 11:30:25 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void env(t_env *env)
{
	t_env	*tempenv;

	tempenv = env;
	while (tempenv)
	{
		printf("%s\n", tempenv->var);
		tempenv = tempenv->next;
	}
}