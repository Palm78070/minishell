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
	SPACE = ' ',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	PIPE = '|',
	REDIRECT_I = '<',
	REDIRECT_O = '>',
	HEREDOC = 8,
	APPEND = 9,
	AND_IF = 10,
	OR_IF = 11
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
//token.c
t_lst	*token_quote(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_space(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_pipe(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_redirect(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_double_sign(t_msh *ms, t_lst *lst, int *index);
//t_lst	*token_and_or(t_msh *ms, t_lst *lst, int *index);
//lexer.c
char    *trim_head(char *s, int delim_indx);
void	ft_lexer(t_msh *ms);
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
