/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/06 22:44:49 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_state(char *s, int i)
{
	if (ft_isalnum(s[i]))
		return (STR);
	if (ft_isspace(s[i]))
		return (SPACE);
	if (s[i + 1])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			return (HEREDOC);
		if (s[i] == '>' && s[i + 1] == '>')
			return (APPEND);
	}
	if (s[i] == '<')
		return (REDIRECT_I);
	if (s[i] == '>')
		return (REDIRECT_O);
	if (s[i] == '\'')
		return (S_QUOTE);
	if (s[i] == '\"')
		return (D_QUOTE);
	if (s[i] == '|')
		return (PIPE);
	return (0);
}

t_lst	*get_quote(t_msh *ms, t_lst *lst, int i)
{
	char	*str_tmp;
	char	quote;

	str_tmp = NULL;
	quote = ms->line[i];
	if (i > 0)
	{
		str_tmp = ft_substr(ms->line, 0, i);
		lst = insertEnd(lst, str_tmp);
		free(str_tmp);
	}
	else
	{
		if (ms->state == S_QUOTE)
			lst = insertEnd(lst, "\'");
		else
			lst = insertEnd(lst, "\"");
	}
	//ms->line = trim_head(ms->line, i);
	//printf("ms->line %s\n", ms->line);
	return (lst);
}

t_lst	*lex_quote(t_msh *ms, t_lst *lst, int i)
{
	char	quote;
	char	*str_tmp;

	quote = ms->line[i];
	str_tmp = NULL;
	lst = get_quote(ms, lst, i);
	ms->line = trim_head(ms->line, i);
	i = 0;
	while (ms->line[i] && ms->line[i] != quote)
		++i;
	str_tmp = ft_substr(ms->line, 0, i);
	lst = insertEnd(lst, str_tmp);
	free(str_tmp);
	ms->line = trim_head(ms->line, --i);
	lst = get_quote(ms, lst, i);
	printf("ms->line after trim %s\n", ms->line);
	ms->line = trim_head(ms->line, i);
	printf("ms->line after trim %s\n", ms->line);
	return (lst);
}

void	ft_token(t_msh *ms)
{
	int	i;
	char	*str_tmp;
	t_lst	*lst;

	i = 0;
	lst = NULL;
	str_tmp = NULL;
	ms->state = 0;
	while (ms->line && ms->line[i])
	{
		ms->state = check_state(ms->line, i);
		if (ms->state == SPACE)
		{
			if (i > 0)
			{
				str_tmp = ft_substr(ms->line, 0, i);
				lst = insertEnd(lst, str_tmp);
				free(str_tmp);
			}
			while (ms->line[i] && ft_isspace(ms->line[i]))
				++i;
			ms->line = trim_head(ms->line, --i);
			i = 0;
		}
		else if (ms->state == PIPE)
		{
			if (i > 0)
			{
				str_tmp = ft_substr(ms->line, 0, i);
				lst = insertEnd(lst, str_tmp);
				free(str_tmp);
			}
			lst = insertEnd(lst, "|");
			ms->line = trim_head(ms->line, i);
			i = 0;
		}
		else if (ms->state == S_QUOTE || ms->state == D_QUOTE)
		{
			/*if (i > 0)
			{
				str_tmp = ft_substr(ms->line, 0, i);
				lst = insertEnd(lst, str_tmp);
				free(str_tmp);
			}
			if (ms->state == S_QUOTE)
				lst = insertEnd(lst, "\'");
			else
				lst = insertEnd(lst, "\"");*/
			lst = lex_quote(ms, lst, i);
			i = 0;
		}
		else
			++i;
	}
	if (ms->line && ms->line[0])
	{
		str_tmp = ft_substr(ms->line, 0, i);
		lst = insertEnd(lst, str_tmp);
		free(str_tmp);
	}
	print_list(lst);
	free_list(lst);
}
