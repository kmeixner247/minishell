/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:09 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/01 16:00:36 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Takes a message and error number
 * and prints out the corresponding error messages
 * If err_num is given the function,
 * looks it up from header and sets lastreturn to it
 *
*/
int	ft_error_msg(t_shell *shell, char *msg, int err_num)
{
	char	*tmp;

	tmp = ft_strjoin("minishell: ", msg);
	if (err_num == 0)
		perror(tmp);
	else
	{
		ft_putendl_fd(tmp, 2);
		shell->lastreturn = err_num;
	}
	free(tmp);
	return (-1);
}

void	ft_error_notfound(t_shell *shell, char *arg)
{
	char	*tmp;

	tmp = ft_strjoin(arg, ": ");
	tmp = ft_strjoin2(tmp, ERR_NOT_FOUND);
	ft_error_msg(shell, tmp, 127);
	free(tmp);
	ft_free_everything(shell);
	exit(127);
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
	ft_error_msg(shell, tmp, 1);
	free(tmp);
}

void	ft_error(t_shell *shell, char *arg, int error)
{
	if (error == ERRNO_NOT_FOUND)
		ft_error_notfound(shell, arg);
	if (error == ERRNO_EXPORT)
		ft_error_export(shell, arg);
	if (error == ERRNO_ENV_ARG)
		ft_error_msg(shell, ERR_ENV_ARG, 1);
	if (error == ERRNO_AMBIG)
		ft_error_ambig(shell, arg);
	if (error == ERRNO_ISDIR)
		ft_error_isdir(shell, arg);
	if (error == ERRNO_UNSET)
		ft_error_unset(shell, arg);
}

void	notfound_or_isdir(t_shell *shell, char *path)
{
	struct stat	*statbuf;

	statbuf = ft_calloc(1, sizeof(struct stat));
	stat(path, statbuf);
	if (S_ISDIR(statbuf->st_mode))
		ft_error(shell, path, ERRNO_ISDIR);
	else
		ft_error(shell, path, ERRNO_NOT_FOUND);
	free(statbuf);
}