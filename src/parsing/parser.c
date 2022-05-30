/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/30 15:20:56 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	parser(t_shell *shell, char *input)
{
	t_token	*token;
	char	**envp;

	envp = get_env(shell->env);
	shell->token = secretary(plumber(input));
	handle_heredocs(shell);
	free(envp);
}
	// quote_handler(shell->token);
