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

void	shell(char **envp)
{
	char	*input;
	t_shell	*shell;

	shell->env = init_env(envp);
	// int i= 0;
	// while (envp[i])
	// 	printf("%s\n", envp[i++]);

	input = readline("minishell$");
	while (42)
	{
		add_history(input);
		if (input && *input && !prechecks(input))
		{
			shell->raw_input = input;
			shell->token = parser(input, shell->env);
			free(input);
			// printtoken(shell->token);
			exec(shell);
		}
		if (!input)
			exit(1);
		input = readline("minishell$");
	}
	rl_clear_history();
	free(input);
	return ;
}
