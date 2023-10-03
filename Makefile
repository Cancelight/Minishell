SRCS = ./main.c \
		./utils.c \
		./signal.c \
		./parser.c \
		./syntax_control.c \
		./readline.c \
		./heredoc.c \
		./input_redirec.c \
		./append_redirec.c \
		./output_redirec.c \
		./duplicate.c
NAME = minishell
CC = gcc
CFLAGS =  -lreadline -g
RM = rm -rf

all: ${NAME}

$(NAME): $(SRCS)
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

clean:

fclean:
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re
