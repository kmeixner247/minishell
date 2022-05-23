/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:32 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 17:57:02 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_free_everything(t_shell *shell)
{
	if (shell->env)
		ft_free_env(&(shell->env));
	if (shell->token)
		ft_free_token(shell->token);
	if (shell->raw_input)
		free(raw_input);
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	tmp = (*env);
	while (env)
	{
		tmp = (*env)->next;
		free(*env);
		(*env) = tmp;
	}
}