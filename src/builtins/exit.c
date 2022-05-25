/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:01:04 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/25 10:07:08 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_isnumeric(char *str);

/**
* @brief cleanly terminate and exit the program
* Check arguments of invocation:
*	if no argument, exit with global error number
*	if one numeric argument, exit with that
*	if more than one, throw error and don't exit
*/
void	ft_exit_minishell(t_shell *shell)
{
	int	nbr_args;
	int	exitcode;

	exitcode = 0;
	nbr_args = ft_nbr_args(shell->token->args);
	if (nbr_args > 2)
	{
		ft_error_msg(shell, ERR_EXIT_COUNT, ERRNO_EXIT_COUNT);
		return ;
	}
	else if (nbr_args == 2 && !(ft_isnumeric(shell->token->args->next->arg)))
	{
		ft_error_msg(shell, ERR_EXIT_ISNUM, ERRNO_EXIT_ISNUM);
		return ;
	}
	else if (nbr_args == 2)
		exitcode = ft_atoi(shell->token->args->next->arg);
	ft_free_everything(shell);
	rl_clear_history();
	exit(exitcode);
}


static int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (0);
		i++;
	}
	return (1);
}
