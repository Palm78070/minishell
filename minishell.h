#ifndef MINISHELL_H
#define MINISHELL_H

# define LLONG_MAX 9223372036854775807

# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
//# include "/usr/local/opt/readline/include/readline"

enum	state
{
	STR = 1,
	SPACE = 2,
	S_QUOTE = 3,
	D_QUOTE = 4,
	PIPE = 5,
	REDIRECT_I = 6,
	REDIRECT_O = 7,
	HEREDOC = 8,
	APPEND = 9
};

typedef struct s_lst
{
	char	*data;
	struct s_lst	*next;
}	t_lst;

typedef struct s_msh
{
	char	*line;
	struct	sigaction	sa;
	int	state;
}	t_msh;

void	ft_handler(int signum);
//lexer.c
void	ft_token(t_msh *ms);
//linked_list.c
void	free_list(t_lst *lst);
void	print_list(t_lst *lst);
t_lst	*insertEnd(t_lst *lst, char *s);
//clear.c
void	ft_clear(t_msh *ms);
void	ft_error(char *s, t_msh *ms);
//readline.c
char	*rl_get(t_msh *ms);
int	is_exit(char *s);
#endif
