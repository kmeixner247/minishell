/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:12:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/23 11:55:20 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tempenv;

	tempenv = env;
	while (tempenv)
	{
		printf("%s\n", tempenv->var);
		tempenv = tempenv->next;
	}
	return (1);
}
