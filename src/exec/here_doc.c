/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:38:55 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/25 15:04:56 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	find_cash_hd(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && !(str[pos] == 36 && \
		(isalnum(str[pos + 1]) || str[pos + 1] == 63 || str[pos + 1] == 95)))
		pos++;
	if (str[pos])
		return (pos);
	else
		return (-1);
}

static char	*get_env_value_hd(char *str, char **envp)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strjoin(str, "=");
	while (envp[i] && ft_strncmp(tmp, envp[i], ft_strlen(tmp)))
		i++;
	free(tmp);
	if (!envp[i])
		return (ft_strdup(""));
	else
	{
		while (envp[i][j] != 61)
			j++;
		j++;
		return (envp[i] + j);
	}
}

static char	*currency_exchange_hd(t_shell *shell, char *str, char **envp)
{
	char	*before;
	char	*replace;
	char	*after;
	char	*varname;

	before = str;
	str += find_cash_hd(str);
	*str = 0;
	str++;
	if (*str == 63)
	{
		replace = ft_strdup(ft_itoa(shell->lastreturn));
		str++;
	}
	else
	{
		varname = find_env_varname(str, envp);
		replace = get_env_value_hd(varname, envp);
		str += ft_strlen(varname);
		free(varname);
	}
	after = str;
	return (ft_strjoin2(ft_strjoin3(before, replace), after));
}

//this accountant is a simplified version of the main one, as it
//doesn't have to handle single quotes
static char	*accountant_hd(t_shell *shell, char *str)
{
	char	*tmp;
	char	**envp;

	envp = get_env(shell->env);
	tmp = str;
	while (find_cash_hd(str) >= 0)
		str = currency_exchange_hd(shell, str, envp);
	if (tmp != str)
		free(tmp);
	free(envp);
	return (str);
}

static char	*my_readline(void)
{
	char	c[2];
	int		i;
	char	*res;

	res = ft_strdup("");
	c[1] = 0;
	i = 1;
	while (i && *c != 10)
	{
		i = read(0, &c, 1);
		if (*c != 10)
			res = ft_strjoin2(res, c);
	}
	return (res);
}

int	here_doc(t_shell *shell, char *delimiter)
{
	int		fds[2];
	char	*line;
	char	*tempfilepath;
	int		openflags;
	int		pid;

	openflags = O_WRONLY | O_CREAT | O_EXCL | O_TRUNC;
	tempfilepath = ft_strjoin3("/tmp/minishell-thd", ft_itoa((int)&delimiter));
	fds[1] = open(tempfilepath, openflags, 0600);
	g_pids = ft_calloc(2, sizeof(int));
	pid = fork();
	if (!pid)
	{
		write(2, "> ", 2);
		line = my_readline();
		while (42)
		{
			if (!line || !ft_strcmp(delimiter, line))
				break ;
			line = accountant_hd(shell, line);
			write(fds[1], line, ft_strlen(line));
			write(fds[1], "\n", 1);
			free(line);
			write(2, "> ", 2);
			line = my_readline();
		}
		free(line);
		close(fds[1]);
		exit(0);
	}
	else
	{
		int status;
		g_pids[0] = pid;
		close(fds[1]);
		wait(&status);
		if (!status)
		{
			free(g_pids);
			g_pids = NULL;
		}
		fds[0] = open(tempfilepath, O_RDONLY);
		unlink(tempfilepath);
		return (fds[0]);
	}
}
