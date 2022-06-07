/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:40:30 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/07 12:11:01 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	*g_pids = NULL;

static void	ft_parse_and_execute(t_shell *shell, char *input)
{
	t_logical	*inputs;
	t_logical	*tmp;
	int			pid;

	pid = 1;
	inputs = split_by_logicals(input);
	tmp = inputs;
	while (tmp)
	{
		if (!(tmp->operator == 2 && !shell->lastreturn) && \
			!(tmp->operator == 1 && shell->lastreturn))
		{
			if (tmp->parentheses == 1)
			{
				pid = fork();
				if (!pid)
				{
					ft_parse_and_execute(shell, tmp->token);
					free_logicals(inputs);
					exit(shell->lastreturn);
					// ft_free_everything(shell);
				}
				else
				{
					waitpid(pid, &shell->lastreturn, 0);
					tmp = tmp->next;
					continue ;
				}
			}
			if (!tmp)
				break ;
			parser(shell, tmp->token);
			exec(shell);
			parsing_cleanup(shell);
			shell->token = NULL;
		}
		tmp = tmp->next;
	}
	free_logicals(inputs);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 1 || argv[1])
	{
		perror("Too many arguments");
		return (1);
	}
	printf("/* ********************************************************** */\n");
	printf("/*                                                            */\n");
	printf("/*                                        :::      ::::::::   */\n");
	printf("/*                                      :+:      :+:    :+:   */\n");
	printf("/*                                    +:+ +:+         +:+     */\n");
	printf("/*   MINISHELL                      +#+  +:+       +#+        */\n");
	printf("/*                                +#+#+#+#+#+   +#+           */\n");
	printf("/*                by jsubel            #+#    #+#             */\n");
	printf("/*               and kmeixner         ###   ########.fr       */\n");
	printf("/*                                                            */\n");
	printf("/* ********************************************************** */\n");
	shell(envp);
	return (0);
}

void	shell(char **envp)
{
	char	*input;
	t_shell	*shell;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell = ft_calloc(sizeof(t_shell), 1);
	shell->env = init_env(envp);
	while (42)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(input);
		if (input && *input && !prechecks(shell, input))
			ft_parse_and_execute(shell, input);
		free(input);
	}
	rl_clear_history();
	ft_free_everything(shell);
	free(input);
	return ;
}
