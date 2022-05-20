/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/20 16:43:42 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token	*parser(char *input, t_env *env)
{
	t_token	*token;
	char	**envp;

	envp = get_env(env);
	token = secretary(plumber(input));
	meta_accountant(token, envp);
	free(envp);
	quote_handler(token);
	return (token);
}
