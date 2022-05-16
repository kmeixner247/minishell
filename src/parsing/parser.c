/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/16 15:37:39 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token *parser(char *input, char **envp)
{
	t_token *token;

	token = secretary(plumber(input));
	meta_accountant(token, envp);
	quote_handler(token);
	return (token);
}