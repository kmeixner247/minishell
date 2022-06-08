/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:59:01 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/08 09:22:49 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_error_notfound(t_shell *shell, char *arg)
{
	char	*tmp;

	tmp = ft_strjoin(arg, ": ");
	tmp = ft_strjoin2(tmp, ERR_NOT_FOUND);
	ft_error_msg(shell, tmp, 127);
	free(tmp);
}

void	ft_error_export(t_shell *shell, char *arg)
{
	char	*tmp;

	tmp = ft_strjoin("export: `", arg);
	tmp = ft_strjoin2(tmp, "': ");
	tmp = ft_strjoin2(tmp, ERR_EXPORT);
	ft_error_msg(shell, tmp, 1);
	free(tmp);
}

void	ft_error_unset(t_shell *shell, char *arg)
{
	char	*tmp;

	tmp = ft_strjoin("unset: `", arg);
	tmp = ft_strjoin2(tmp, "': ");
	tmp = ft_strjoin2(tmp, ERR_EXPORT);
	ft_error_msg(shell, tmp, 1);
	free(tmp);
}

void	ft_error_ambig(t_shell *shell, char *arg)
{
	char	*tmp;

	tmp = ft_strjoin(arg, ": ");
	tmp = ft_strjoin2(tmp, ERR_AMBIG);
	ft_error_msg(shell, tmp, 1);
	free(tmp);
}

void	ft_error_isdir(t_shell *shell, char *arg)
{
	char	*tmp;

	tmp = ft_strjoin(arg, ": ");
	tmp = ft_strjoin2(tmp, ERR_ISDIR);
	ft_error_msg(shell, tmp, 126);
	free(tmp);
}
