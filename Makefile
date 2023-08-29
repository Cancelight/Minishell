SRCS = ./main.c \
		./utils.c \
		./signal.c \
		./parser.c \
		./syntax_control.c \
		./readline.c
NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -lreadline
RM = rm -rf
LIBC = ar -rcs

all: ${NAME}

$(NAME): $(SRCS)
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)

clean:

fclean:
	@${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re
