/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:48:23 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/27 12:50:59 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	sigint_interactive(void)
{
	printf("minishell$ %s  ", rl_line_buffer);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGINT)
	{
		if (g_pids)
		{
			if (g_pids[0] < 0)
				kill(g_pids[1], SIGUSR1);
			else
			{
				printf("\n");
				while (g_pids[i])
				{
					kill(g_pids[i], SIGKILL);
					i++;
				}
			}
		}
		else
			sigint_interactive();
	}
}
