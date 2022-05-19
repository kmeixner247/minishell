/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/19 13:04:41 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exec_builtins(t_args *args, t_env *env)
{
	int	result;

	result = 0;
	if (ft_strcmp(args->arg, "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args->arg, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args->arg, "cd") == 0)
	{
		printf("sheesh.\n");
		result = ft_cd(args, env);
	}
	return (result);
}
