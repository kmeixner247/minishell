/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:23:32 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/08 13:03:47 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	handle_logicals(t_shell *shell, char *input);

void	parser(t_shell *shell, char *input)
{
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

static void	logical_child(t_shell *shell, t_logical *tmp, t_logical *inputs)
{
	handle_logicals(shell, tmp->token);
	free_logicals(inputs);
	exit(shell->lastreturn);
}

static void	ft_parse_and_execute(t_shell *shell, t_logical *tmp)
{
	parser(shell, tmp->token);
	exec(shell);
	parsing_cleanup(shell);
	shell->token = NULL;
}

static int	handle_pars(t_shell *shell, t_logical *tmp, t_logical *inputs)
{
	int	pid;

	pid = fork();
	if (!pid)
		logical_child(shell, tmp, inputs);
	else
	{
		waitpid(pid, &shell->lastreturn, 0);
		tmp = tmp->next;
		return (1);
	}
	return (0);
}

void	handle_logicals(t_shell *shell, char *input)
{
	t_logical	*inputs;
	t_logical	*tmp;

	inputs = split_by_logicals(input);
	tmp = inputs;
	while (tmp)
	{
		if (!(tmp->operator == 2 && !shell->lastreturn) && \
			!(tmp->operator == 1 && shell->lastreturn))
		{
			if (tmp->parentheses == 1)
				handle_pars(shell, tmp, inputs);
			else
				ft_parse_and_execute(shell, tmp);
		}
		tmp = tmp->next;
	}
	free_logicals(inputs);
}
