NAME		= minishell
GCC			= gcc
FLAGS		= -Wall -Wextra -Werror -ggdb3 -O0
SRC_PATH	= src
LIBFT		= libft
BI			= builtins/
EXEC		= exec/
PAR			= parsing/
SRC_FILES 	=	main.c \
				$(BI)builtin_handler.c \
				$(BI)echo.c \
				$(BI)pwd.c \
				$(EXEC)exec.c \
				$(EXEC)here_doc.c \
				$(EXEC)redirs.c \
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