NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra -lreadline

LIBFT = libft/libft.a
LIBFT_FLAGS = -Llibft

SRCS = minishell.c \
	readline.c \

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
