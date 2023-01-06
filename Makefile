NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra -lreadline

LIBFT = ./libft/libft.a
#LIBFT_FLAGS = -Llibft
LIB_I = -I./libft/

#READLINE = -Iusr/local/opt/readline/include
#READLINE_FLAGS = -Lusr/local/opt/readline

SRCS = minishell.c \
	readline.c \
	lexer.c \
	linked_list.c \
	clear.c \

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $^ $(LIB_I) -o $@ 
	#$(CC) $(CFLAGS) $^ $(LIB_INC) $(LIBFT_FLAGS) -o $@ 

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
