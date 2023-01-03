#ifndef MINISHELL_H
#define MINISHELL_H

# define LLONG_MAX 9223372036854775807

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
//# include "/usr/local/opt/readline/include/readline"

typedef struct s_msh
{
	char	*line;
	struct	sigaction	sa;
}	t_msh;

void	ft_handler(int signum);
//clear.c
void	ft_clear(t_msh *ms);
void	ft_error(char *s, t_msh *ms);
//readline.c
char	*rl_get(t_msh *ms);
int	is_exit(char *s);
#endif
