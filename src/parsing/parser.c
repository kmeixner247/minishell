/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/04 16:20:39 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	parser(t_shell *shell, char *input)
{
	t_token	*token;
	char	**envp;
	char	*tmp;

	tmp = ft_strdup(input);
	envp = get_env(shell->env);
	tmp = accountant(shell, tmp);
	shell->token = secretary(plumber(tmp));
	handle_heredocs(shell);
	free(envp);
	free(tmp);
}
