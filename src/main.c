	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   main.c                                             :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2022/05/13 10:40:30 by jsubel            #+#    #+#             */
	/*   Updated: 2022/05/13 10:54:04 by jsubel           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#include "../incl/minishell.h"

int *g_pids = NULL;

int	main(int argc, char **argv, char **envp)
{
	if (argc < 1 || argv[1])
	{
		perror("Too many arguments");
		return (1);
	}
	printf("/* ************************************************************************** */\n");
	printf("/*                                                                            */\n");
	printf("/*                                                        :::      ::::::::   */\n");
	printf("/*                                                      :+:      :+:    :+:   */\n");
	printf("/*                                                    +:+ +:+         +:+     */\n");
	printf("/*   MINISHELL                                      +#+  +:+       +#+        */\n");
	printf("/*                                                +#+#+#+#+#+   +#+           */\n");
	printf("/*                                by jsubel            #+#    #+#             */\n");
	printf("/*                               and kmeixner         ###   ########.fr       */\n");
	printf("/*                                                                            */\n");
	printf("/* ************************************************************************** */\n");
	shell(envp);
	return (0);
}

//	this is just temporarily here for testing
void	printtoken(t_token *token)
{
	t_args	*args;
	t_redir	*redir;

	while (token)
	{
		printf("-------------NEW TOKEN------------\n");
		printf("PID: %d\n", token->pid);
		args = token->args;
		printf("---------------ARGS---------------\n");
		while (args)
		{
			printf("%s\n", args->arg);
			args = args->next;
		}
		printf("----------------------------------\n");
		redir = token->redir;
		printf("--------------REDIRS--------------\n");
		while (redir)
		{
			printf("%d: %s\n", redir->id, redir->filename);
			redir = redir->next;
		}
		printf("----------------------------------\n");
		token = token->next;
	}
}

void	handle_signals(int sig)
{
	int	i;

	ft_putstr_fd("hello\n", 2);
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
		{
			printf("minishell$ %s  ", rl_line_buffer);
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT)
	{
		printf("minishell$ %s  \b\b", rl_line_buffer);
	}
}

void	shell(char **envp)
{
	char				*input;
	t_shell				*shell;

	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
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
		if (input && *input && !prechecks(input))
		{
			parser(shell, input);
			exec(shell);
			// printtoken(shell->token);
			g_pids[0] = 0;
			free(g_pids);
			g_pids = NULL;
			parsing_cleanup(shell->token);
		}
		free(input);
	}
	rl_clear_history();
	// ft_free_everything(shell);
	free(input);
	return ;
}
