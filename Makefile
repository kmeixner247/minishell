NAME		= minishell
GCC			= gcc
FLAGS		= -Wall -Wextra -Werror -ggdb3 -O0
SRC_PATH	= src
LIBFT		= libft
BI			= builtins/
PAR			= parsing/
SRC_FILES 	=	main.c \
				$(BI)echo.c \
				$(BI)pwd.c \
				$(PAR)accountant.c \
				$(PAR)parser.c \
				$(PAR)plumber.c \
				$(PAR)prechecks.c \
				$(PAR)quotes.c \
				$(PAR)secretary.c \
				$(PAR)utils_accountant.c \
				$(PAR)utils_args.c \
				$(PAR)utils_redir.c \
				$(PAR)utils_tokens.c \
				$(PAR)utils_parsing.c \
				pipeTESTS/pipesDONTUSETHIS.c \
				pipeTESTS/here_doc.c \
				pipeTESTS/redirs.c

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_FILES))

all: lib $(NAME)

lib:
	make -C $(LIBFT)

$(NAME): $(SRC) $(LIBFT)/libft.a
	$(GCC) $^ -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(LIBFT) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -l readline  -o $(NAME)

clean:
	make clean -C $(LIBFT)
	rm $(NAME)

fclean: clean
	rm $(LIBFT)/libft.a

re: clean all