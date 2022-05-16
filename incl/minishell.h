/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:53:46 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/16 12:01:36 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>		// readline, printf
# include <stdlib.h>	// malloc, free, exit, getenv,
# include <fcntl.h>		// open
# include <unistd.h>	// access, unlink, close, read, write,
						// pipe, dup, dup2, execve, fork, getcwd, chdir,
						// stat, lstat, fstat, isatty, ttyname, ttyslot,
						// ioctl
# include <sys/wait.h>	// waitpid, wait, wait3, wait4
# include <signal.h>	// signal, sigaction, kill
# include <sys/types.h>	// opendir, closedir
# include <dirent.h>	// readdir
# include <stdio.h>		// perror
# include <string.h>	// strerror
# include <termios.h>	// tcsetattr, tcgetattr
# include <curses.h>	// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"
# include <sys/param.h>	// max path len


void		shell(char **envp);
char		*readline(const char *);

// execution
int	ft_exec_builtins(char **args);

// builtins
int	ft_echo(char **args);
int	ft_pwd(char **args);

//utils
int	ft_strcmp(const char *s1, const char *s2);

#endif