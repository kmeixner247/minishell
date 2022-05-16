NAME		= minishell
GCC			= gcc
FLAGS		= -Wall -Wextra -Werror -ggdb3 -O0
SRC_PATH	= src
SRC_FILES 	= main.c \

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_FILES))

all: $(NAME)

$(NAME): $(SRC)
	$(GCC) $^ -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -l readline -o $(NAME)

clean:
	rm $(NAME)

re: clean all