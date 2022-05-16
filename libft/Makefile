# -*- MakeFile -*-

SRC = 	ft_abs.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_end_process.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strjoin2.c \
		ft_strjoin3.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strmapi.c \
		ft_striteri.c \

BONUS_SRC = ft_lstadd_back.c \
		 	ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \


BONUS_OBJS = $(BONUS_SRC:.c=.o)

OBJS = $(SRC:.c=.o)

HDRS    = libft.h

NAME    = libft.a

RM  = rm -rf

GCC = gcc

AR  = ar -crs

FLAGS   = -Wall -Wextra -Werror

.c.o: $(SRC) $(HDRS)
	$(GCC) $(FLAGS) -c -o $@ $<

$(NAME):	$(OBJS) $(HDRS)
	$(AR) $(NAME) $(OBJS) $@ $^

all:	$(NAME)

bonus:	$(OBJS) $(BONUS_OBJS) $(HDRS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

re:	clean fclean all

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	$(RM) $(NAME)

.PHONY:
	all clean fclean re bonus