/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/03 19:24:16 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	parser(t_shell *shell, char *input)
{
	t_token	*token;
	char	**envp;
	char	*test;

	test = ft_strdup(input);
	envp = get_env(shell->env);
	test = accountant(shell, test);
	shell->token = secretary(plumber(test));
	handle_heredocs(shell);
	free(envp);
	free(test);
}
	// quote_handler(shell->token);
