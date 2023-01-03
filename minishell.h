#ifndef MINISHELL_H
#define MINISHELL_H

# define LLONG_MAX 9223372036854775807

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

//readline.c
char	*rl_get();
int	is_exit(char *s);
#endif
