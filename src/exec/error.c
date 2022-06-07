/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:09 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/07 08:58:58 by jsubel           ###   ########.fr       */
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

int	notfound_or_isdir(t_shell *shell, char *path, char **ar, char **ev)
{
	struct stat	*statbuf;
	int			err;

	statbuf = ft_calloc(1, sizeof(struct stat));
	stat(path, statbuf);
	if (S_ISDIR(statbuf->st_mode))
	{
		ft_error(shell, path, ERRNO_ISDIR);
		err = 126;
	}
	else if (errno == EACCES)
	{
		ft_error_msg(shell, shell->token->args->arg, 0);
		err = 126;
	}
	else
	{
		ft_error(shell, path, ERRNO_NOT_FOUND);
		err = 127;
	}
	free(statbuf);
	ft_free_everything(shell);
	return (err);
}
