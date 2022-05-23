/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:53:46 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 14:47:17 by jsubel           ###   ########.fr       */
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


typedef struct s_shell
{
	struct s_token	*token;
	struct s_env	*env;
	int				lastreturn;
	char			*raw_input;
}					t_shell;

typedef struct s_token
{
	struct s_args	*args;
	struct s_redir	*redir;
	struct s_token	*next;
	int				infd;
	int				outfd;
}					t_token;

typedef struct s_redir
{
	int				id;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

void		shell(char **envp);
// char		*readline(const char *str);

/*---------------------------------------------------------------------------*/
/*                                 EXECUTION                                 */
/*---------------------------------------------------------------------------*/
int	ft_exec_builtins(t_shell *shell);

// builtins
int	ft_echo(t_args *args);
int	ft_pwd(void);
int	ft_cd(t_args *args, t_env *env);
int	ft_env(t_env *env);
int	ft_export(t_env **env, char**args);
int	ft_unset(t_env **env, char **args);

//exit
int		ft_exit_minishell(t_shell *shell);
void	ft_error_minishell(t_token *token);
void	ft_error_msg(char *msg);
//utils_env
t_env	*new_env(char *var);
void	env_addback(t_env **start, t_env *new);
t_env	*init_env(char **envp);

// builtin-handler.c
int			isbuiltin(char *arg);

// exec.c
void		exec(t_shell *shell);

// here_doc.c
int			here_doc(char *delimiter, char **envp);

// redirs.c
void		handle_redirs(t_shell *shell);

/*---------------------------------------------------------------------------*/
/*                                  PARSING                                  */
/*---------------------------------------------------------------------------*/
// env.c
void		env(t_env *env);

// utils_env.c
t_env		*new_env(char *var);
void		env_addback(t_env **start, t_env *new);
t_env		*init_env(char **envp);
char		**get_env(t_env *env);

// export.c
void		export(t_env **env, char**args);

// unset.c
void		unset(t_env **env, char **args);

// parsing
// parser.c
t_token		*parser(char *input, t_env *env);

// accountant.c
void		meta_accountant(t_token *token, char **envp);
char		*currency_exchange(char *str, char **envp);

// plumber.c
char		**plumber(char *str);

// prechecks.c
int			prechecks(char *str);

// quotes.c
void		quote_handler(t_token *token);
int			quote_skipper(char *str);

// secretary.c
t_token		*secretary(char **arr);

// utils_accountant.c
int			find_cash(char *str, int *doubflag);
char		*find_env_var(char *str, char **envp, int doubflag);
char		*find_env_varname(char *str, char **envp);
char		*get_env_value(char *str, char **envp, int doubflag);

// utils_args.c
t_args		*new_args(void);
void		args_addback(t_args **start, t_args *new);
char		**get_args(t_token *token);
int			ft_nbr_args(t_args *args);
//	utils_redir.c
t_redir		*new_redir(void);
void		redir_addback(t_redir **start, t_redir *new);

// utils_tokens.c
t_token		*new_token(void);
void		token_addback(t_token **start, t_token *new);

// utils_parsing.c
int			check_char(unsigned char c, const char *str);

#endif