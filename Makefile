SRCS = ./src/main.c \
		./src/utils.c \
		./src/reset_utils.c \
		./src/libft_split.c \
		./src/signal/signal.c \
		./src/parser/parser.c \
		./src/parser/parser_utils.c \
		./src/parser/parser_utils_2.c \
		./src/syntax_control.c \
		./src/readline.c \
		./src/redirection/heredoc.c \
		./src/redirection/input.c \
		./src/redirection/append.c \
		./src/redirection/output.c \
		./src/redirection/duplicate.c \
		./src/redirection/general.c \
		./src/redirection/redirection_utils.c \
		./src/redirection/redirection_utils_2.c
NAME = minishell
CC = gcc
CFLAGS =  -lreadline  -g
RM = rm -rf

all: ${NAME}

$(NAME): $(SRCS)
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

clean:

fclean:
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re
