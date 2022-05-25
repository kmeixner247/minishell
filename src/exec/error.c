/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:09 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/25 10:07:17 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Takes a message and error number and prints out the corresponding error messages
 * If err_num is given the function, looks it up from header and sets lastreturn to it
 *
*/
void	ft_error_msg(t_shell *shell, char *msg, int err_num)
{
	char *tmp;

	tmp = ft_strjoin("minishell: ", msg);
	if (err_num == 0)
		perror(tmp);
	else
	{
		ft_putendl_fd(tmp, 2);
		shell->lastreturn = err_num;
	}
	free(tmp);
}
