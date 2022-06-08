NAME		= minishell
GCC			= gcc
FLAGS		= -Wall -Wextra -Werror -O3
SRC_PATH	= src
LIBFT		= libft
BI			= builtins/
EXEC		= exec/
PAR			= parsing/
MISC		= misc/
SRC_FILES 	=	main.c \
				$(BI)builtin_handler.c \
				$(BI)cd.c \
				$(BI)echo.c \
				$(BI)env.c \
				$(BI)exit.c \
				$(BI)export.c \
				$(BI)pwd.c \
				$(BI)unset.c \
				$(BI)utils_env.c \
				$(BI)utils_export.c \
				$(EXEC)error.c \
				$(EXEC)exec.c \
				$(EXEC)free.c \
				$(EXEC)here_doc.c \
				$(EXEC)redirs.c \
				$(EXEC)utils_error.c \
				$(EXEC)utils_exec.c \
				$(EXEC)utils_here_doc.c \
				$(PAR)accountant.c \
				$(PAR)logicals.c \
				$(PAR)parser.c \
				$(PAR)parsing_cleanup.c \
				$(PAR)plumber.c \
				$(PAR)prechecks_pars_logicals.c \
				$(PAR)prechecks.c \
				$(PAR)quotes.c \
				$(PAR)secretary.c \
				$(PAR)utils_accountant.c \
				$(PAR)utils_args.c \
				$(PAR)utils_logicals.c \
				$(PAR)utils_redir.c \
				$(PAR)utils_tokens.c \
				$(PAR)utils_wildcard.c \
				$(PAR)wildcard.c \
				$(MISC)signals.c \
				$(MISC)utils.c

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_FILES))

all: lib $(NAME)

lib:
	make -C $(LIBFT)

$(NAME): $(SRC) $(LIBFT)/libft.a
	$(GCC) $(FLAGS) $^ -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(LIBFT) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -l readline  -o $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -f $(NAME)

fclean: clean
	rm -f $(LIBFT)/libft.a
	rm -rf *.dSYM

re: clean all