/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:32 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/29 19:00:02 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_free_everything(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	if (shell->token)
		parsing_cleanup(shell);
	free(shell);
}
