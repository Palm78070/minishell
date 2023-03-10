#include "minishell.h"

char	*trim_head(char *s, int delim_indx)
{
	int i = -1;
	int len = ft_strlen(s) - delim_indx;
	char *res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (s[++delim_indx])
		res[++i] = s[delim_indx];
	res[++i] = '\0';
	free(s);
	return (res);
}

static int	is_double_arrow(char *s, int i)
{
	if (s[i + 1])
		return (s[i + 1] == '<' || s[i + 1] == '>');	
	return (0);
}

int	check_state(char *s, int i)
{
	if (ft_isalnum(s[i]))
		return (STR);
	else if (ft_isspace(s[i]))
		return (SP);
	else if ((s[i] == '<' || s[i] == '>') && is_double_arrow(s, i))
	{
		if (s[i] == '<' && s[i + 1] == '<')
			return (HEREDOC);
		if (s[i] == '>' && s[i + 1] == '>')
			return (APPEND);
	}
	else if (s[i] == '<')
		return (REDIRECT_I);
	else if (s[i] == '>')
		return (REDIRECT_O);
	else if (s[i] == '\'')
		return (S_QUOTE);
	else if (s[i] == '\"')
		return (D_QUOTE);
	else if (s[i] == '|' && s[i + 1] && s[i + 1] == '|')
		return (OR_IF);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '&' && s[i + 1] && s[i + 1] == '&')
		return (AND_IF);
	return (0);
}

t_lst	*insert_str(t_msh *ms, t_lst *lst, int i)
{
	char	*str_tmp;

	str_tmp = NULL;
	str_tmp = ft_substr(ms->line, 0, i);
	lst = insertEnd(lst, str_tmp);
	free(str_tmp);
	return (lst);
}
