/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:08:10 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/19 19:08:23 by kmeixner         ###   ########.fr       */
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
