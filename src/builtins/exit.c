/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:01:04 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 14:59:15 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
* @brief cleanly terminate and exit the program
* Check arguments of invocation:
*	if no argument, exit with global error number
*	if one numeric argument, exit with that
*	if more than one, throw error and don't exit
*/
int	ft_exit_minishell(t_shell *shell)
{
	int	nbr_args;

	nbr_args = ft_nbr_args(shell->token->args);
	
	return (1);
}

void	ft_error_msg(char *msg)
{
	char *tmp;

	tmp = ft_strjoin("minishell: ", msg);
	perror(tmp);
}