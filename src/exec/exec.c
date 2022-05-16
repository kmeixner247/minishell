/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:35:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/16 12:06:18 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exec_builtins(char **args)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd(args);
	return (result);
}
