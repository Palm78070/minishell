NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra -lreadline

LIBFT = libft/libft.a
LIBFT_FLAGS = -Llibft

#READLINE = -Iusr/local/opt/readline/include
#READLINE_FLAGS = -Lusr/local/opt/readline

SRCS = minishell.c \
	readline.c \
	lexer.c \
	clear.c \

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) -o $@ 

$(LIBFT):
	@make -C ./libft

norminette:
	norminette -R CheckForbiddenSourceHeader *.h *.c

clean:
	@make fclean -C ./libft
	rm -rf *.dSYM *.o $(NAME)

fclean: clean

re: fclean all libft

.PHONY: clean fclean re norminette libft
