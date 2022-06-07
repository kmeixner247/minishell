/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:53:46 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/07 11:23:07 by kmeixner         ###   ########.fr       */
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
# include <sys/stat.h>	// stat
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

# define ERR_TEMPLATE "Error: message goes here"
# define ERR_EXIT_COUNT "too many arguments"
# define ERRNO_EXIT_COUNT 10
# define ERR_EXIT_ISNUM	 "argument is not numeric"
# define ERRNO_EXIT_ISNUM 255
# define ERR_AMBIG "ambiguous redirect"
# define ERRNO_AMBIG 12
# define ERR_UNCLOSED_QUOTES "syntax error: unclosed quotes"
# define ERRNO_UNCLOSED_QUOTES 13
# define ERR_PIPE_INPUT "syntax error: no valid input before or after pipe"
# define ERRNO_PIPE_INPUT 14
# define ERR_REDIR_INPUT "syntax error: no valid input after redirection"
# define ERRNO_REDIR_INPUT 15
# define ERR_NOT_FOUND "command not found"
# define ERRNO_NOT_FOUND 127
# define ERR_ENV_ARG "illegal argument in env"
# define ERRNO_ENV_ARG 16
# define ERR_EXPORT "not a valid identifier"
# define ERRNO_EXPORT 17
# define ERR_ISDIR "is a directory"
# define ERRNO_ISDIR 18
# define ERR_UNSET "not a valid identifier"
# define ERRNO_UNSET 19
# define ERR_HOME_UNSET "HOME not set"
# define ERRNO_HOME_UNSET 20
# define ERR_PAR_DIR "chdir: error retrieving current directory: \
getcwd: cannot access parent directories"
# define ERRNO_PAR_DIR 21
# define ERR_LOGICS_INPUT "syntax error: no valid input after logical operator"
# define ERRNO_LOGICS_INPUT 22
# define ERR_PARENTH_INPUT "syntax error: invalid use of parentheses"
# define ERRNO_PARENTH_INPUT 23
extern int	*g_pids;

typedef struct s_logical
{
	char				*token;
	int					operator;
	int					parentheses;
	struct s_logical	*next;
}						t_logical;

/**
 * @brief Main structure holding all the other structs
 * @param token one token per command, saved as a linked list
 * @param env environmental variables, saved as a linked list
 * @param lastreturn return of last process, saved for $?
 * @param raw_input raw user input for safekeeping and debugging
 */

typedef struct s_shell
{
	struct s_token	*token;
	struct s_env	*env;
	int				lastreturn;
	char			*raw_input;
}					t_shell;

/**
 * @brief Token structure, containing the used commands,
 * redirections, file descriptors for infile and outfile and process id
 * @param args linked list of command and its args
 * @param redir linked list of any redirects that apply to this token
 * @param next pointer to next element of list
 * @param pid process id of token process
 * @param infd file descriptor of the infile
 * @param outfd file descriptor of the outfile
 */
typedef struct s_token
{
	struct s_args	*args;
	struct s_redir	*redir;
	struct s_token	*next;
	int				pid;
	int				infd;
	int				outfd;
}					t_token;

/**
 * @brief Redirection structure, containing information
 	about any redirections for its token
 * @param id 1 for redirected input, 2 for here_doc,
 	3 for redirected output and 4 for append to file
 * @param filename filename of redirection
 * @param next pointer to next element of list
 */
typedef struct s_redir
{
	int				id;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

/**
 * @brief Arguments structure, containg the command
	and its flags and arguments to be executed
 * @param args each word of the command, separated by empty spaces,
 	the first one being the command
 * @param next pointer to next element of list
 */
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

// builtins

int			ft_echo(t_shell *shell, t_args *args);
int			ft_pwd(void);
int			ft_export(t_shell *shell, t_token *token);
int			ft_unset(t_shell *shell);

// exit

void		ft_error_minishell(t_token *token);
int			ft_cd(t_shell *shell, t_args *args, t_env *env);
int			ft_env(t_shell *shell, t_token *token);

int			ft_exit_minishell(t_shell *shell, int tempfd);

// utils_env.c

t_env		*new_env(char *var);
void		env_addback(t_env **start, t_env *new);
t_env		*init_env(char **envp);
char		**get_env(t_env *env);
int			free_env(t_env *env);
// in cd
t_env		*ft_find_element(t_env *env, char *str);

// utils_export.c

char		*get_varname(char *arg);
int			is_valid_varname(char *arg);
void		print_alphabetical(t_env *env);

// builtin-handler.c

int			isbuiltin(char *arg);

// exec.c

void		exec(t_shell *shell);

// here_doc.c

void		handle_heredocs(t_shell *shell);

// utils_here_doc.c

void		hd_newline(int sig);
char		*accountant_hd(t_shell *shell, char *str);

//utils_exec.c

void		write_pids(t_shell *shell);
void		assign_pipes(t_token *token, int pipefds[2]);
void		try_paths(t_shell *shell, char **args, char **envp);
int			ft_exec_builtins(t_shell *shell, t_token *token, int tempfd);
void		ft_meta_wild_quote(t_shell *shell, t_token *token);

// redirs.c

int			handle_redirs_single(t_shell *shell, t_token *token);

// error.c

int			ft_error_msg(t_shell *shell, char *msg, int err_num);
void		ft_error_handler(t_shell *shell, char *msg, int err_num);
void		ft_error(t_shell *shell, char *arg, int error);
int			notfound_or_isdir(t_shell *shell, char *path, char **ar, char **ev);

// free.c

void		ft_free_everything(t_shell *shell);

/*---------------------------------------------------------------------------*/
/*                                  PARSING                                  */
/*---------------------------------------------------------------------------*/
// parser.c

void		parser(t_shell *shell, char *input);

// parsing_cleanup.c

int			parsing_cleanup(t_shell *shell);

// accountant.c

char		*accountant(t_shell *shell, char *str);
void		meta_accountant(t_shell *shell, t_token *token);
char		*currency_exchange(t_shell *shell, char *str, char **envp);

// plumber.c

char		**plumber(char *str);

// logicals.c

char		*has_logical(char *str);
void		logical_addback(t_logical **start, t_logical *new);
t_logical	*new_logical(char *str);
t_logical	*split_by_logicals(char *input);
void		free_logicals(t_logical *logical);

// prechecks.c

int			prechecks(t_shell *shell, char *str);

// quotes.c

void		quote_handler(t_token *token);
int			quote_skipper(char *str);
char		*replace_string(char *str);
int			quotecount(char *str);

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
char		**get_args(t_args *args);
int			ft_nbr_args(t_args *args);
void		args_delfirst(t_args **args);

//	utils_redir.c

t_redir		*new_redir(void);
void		redir_addback(t_redir **start, t_redir *new);

// utils_tokens.c

t_token		*new_token(void);
void		token_addback(t_token **start, t_token *new);

// utils_parsing.c

int			check_char(unsigned char c, const char *str);

void		handle_sigint(int sig);

// wildcard.c

int			redir_wildcard(t_shell *shell, t_redir *redir);
void		meta_args_wildcard(t_token *token);

void		printtoken(t_token **tokenn);

// utils_wildcard.c

int			haswildcard(char *str);
void		ft_important_function(t_args *args);
int			match(char *pattern, char *str);

#endif