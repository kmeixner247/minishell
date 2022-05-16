NAME		= minishell
GCC			= gcc
FLAGS		= -Wall -Wextra -Werror -ggdb3 -O0
SRC_PATH	= src
LIBFT		= 42_libft
BI			= builtins/
SRC_FILES 	=	main.c \
				$(BI)echo.c \
				$(BI)pwd.c \


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