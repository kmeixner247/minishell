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

void	shell(char **envp)
{
	char *input;

	input = readline("minishell$");
	free(input);
	return ;
}