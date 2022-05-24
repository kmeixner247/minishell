/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:32 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 18:02:21 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_free_everything(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	if (shell->token)
		parsing_cleanup(shell->token);
	if (shell->raw_input)
		free(shell->raw_input);
	free(shell);
}
