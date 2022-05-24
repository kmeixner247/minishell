/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/24 12:46:56 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	parser(t_shell *shell, char *input, t_env *env)
{
	t_token	*token;
	char	**envp;

	envp = get_env(env);
	token = secretary(plumber(input));
	meta_accountant(shell, token, envp);
	free(envp);
	quote_handler(token);
	shell->token = token;
}
