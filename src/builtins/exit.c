/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:01:04 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/05 14:09:07 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_isnumeric(char *str);
static void	ft_exit_cleanup(t_shell *shell, int tempfd);

/**
* @brief cleanly terminate and exit the program
* Check arguments of invocation:
*   if no argument, exit with global error number
*	if first argument non-numeric, throw error and don't exit
*	if one numeric argument, exit with that
*	if more than one, throw error and don't exit
*/
int	ft_exit_minishell(t_shell *shell, int tempfd)
{
	int	nbr_args;
	int	exitcode;

	exitcode = 0;
	if (!shell->token->next)
		ft_putendl_fd("exit", 2);
	nbr_args = ft_nbr_args(shell->token->args);
	if (nbr_args == 1)
		exitcode = shell->lastreturn;
	else if (!(ft_isnumeric(shell->token->args->next->arg)))
	{
		ft_error_msg(shell, ERR_EXIT_ISNUM, ERRNO_EXIT_ISNUM);
		exitcode = 255;
	}
	else if (nbr_args > 2)
	{
		ft_error_msg(shell, ERR_EXIT_COUNT, ERRNO_EXIT_COUNT);
		return (1);
	}
	else if (nbr_args == 2)
		exitcode = ft_atoi(shell->token->args->next->arg);
	ft_exit_cleanup(shell, tempfd);
	exit(exitcode);
	return (0);
}

/** @brief clear memory and close file descriptor if applicable */
static void	ft_exit_cleanup(t_shell *shell, int tempfd)
{
	ft_free_everything(shell);
	rl_clear_history();
	if (tempfd > 0)
		close(tempfd);
}

/** @brief check if a string is fully numeric */
static int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
