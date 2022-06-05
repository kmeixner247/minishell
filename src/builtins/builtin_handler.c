/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:08:10 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/05 13:21:59 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	isbuiltin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || \
		!ft_strcmp(arg, "cd") || \
		!ft_strcmp(arg, "pwd") || \
		!ft_strcmp(arg, "export") || \
		!ft_strcmp(arg, "unset") || \
		!ft_strcmp(arg, "env") || \
		!ft_strcmp(arg, "exit"))
		return (1);
	else
		return (0);
}

int	ft_exec_builtins(t_shell *shell, t_token *token, int tmpfd)
{
	int		result;
	t_args	*args;
	int		tempfd;

	args = token->args;
	result = 0;
	if (ft_strcmp(args->arg, "echo") == 0)
		result = ft_echo(shell, args);
	if (ft_strcmp(args->arg, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args->arg, "cd") == 0)
		result = ft_cd(shell, args, shell->env);
	if (ft_strcmp(args->arg, "env") == 0)
		result = ft_env(shell, token);
	if (ft_strcmp(args->arg, "export") == 0)
		result = ft_export(shell, token);
	if (ft_strcmp(args->arg, "unset") == 0)
		result = ft_unset(shell);
	if (ft_strcmp(args->arg, "exit") == 0)
		result = ft_exit_minishell(shell, tmpfd);
	return (result);
}
