/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/07 23:07:20 by rthammat         ###   ########.fr       */
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
	else if (ft_isspace(s[i]))
		return (SPACE);
	else if ((s[i] == '<' || s[i] == '>') && s[i + 1])
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
	else if (s[i] == '|')
		return (PIPE);
	return (0);
}

t_lst	*token_quote(t_msh *ms, t_lst *lst, int *index)
{
	char	quote;
	char	*str_tmp;
	int	i;

	i = *index;
	quote = ms->line[i];
	str_tmp = NULL;
	++i;
	while (ms->line[i] && ms->line[i] != quote)
		++i;
	str_tmp = ft_substr(ms->line, 0, ++i);
	lst = insertEnd(lst, str_tmp);
	free(str_tmp);
	ms->line = trim_head(ms->line, --i);
	*index = 0;
	return (lst);
}

t_lst	*token_space(t_msh *ms, t_lst *lst, int *index)
{
	char	*str_tmp;
	int	i;

	str_tmp = NULL;
	i = *index;
	if (i > 0)
	{
		str_tmp = ft_substr(ms->line, 0, i);
		lst = insertEnd(lst, str_tmp);
		lst = insertEnd(lst, " ");
		free(str_tmp);
	}
	while (ms->line[i] && ft_isspace(ms->line[i]))
		++i;
	ms->line = trim_head(ms->line, --i);
	*index = 0;
	return (lst);
}

t_lst	*token_pipe(t_msh *ms, t_lst *lst, int *index)
{
	char	*str_tmp;
	int	i;

	str_tmp = NULL;
	i = *index;
	if (i > 0)
	{
		str_tmp = ft_substr(ms->line, 0, i);
		lst = insertEnd(lst, str_tmp);
		free(str_tmp);
	}
	lst = insertEnd(lst, "|");
	ms->line = trim_head(ms->line, i);
	*index = 0;
	return (lst);
}

t_lst	*token_redirect(t_msh *ms, t_lst *lst, int *index)
{
	char	*str_tmp;
	int	i;

	str_tmp = NULL;
	i = *index;
	if (i > 0)
	{
		str_tmp = ft_substr(ms->line, 0, i);
		lst = insertEnd(lst, str_tmp);
		free(str_tmp);
	}
	if (ms->state == REDIRECT_I)
		lst = insertEnd(lst, "<");
	else if (ms->state == REDIRECT_O)
		lst = insertEnd(lst, ">");
	ms->line = trim_head(ms->line, i);
	*index = 0;
	return (lst);
}

t_lst	*token_double_arrow(t_msh *ms, t_lst *lst, int *index)
{
	char	*str_tmp;
	int	i;
	char	quote;

	str_tmp = NULL;
	i = *index;
	if (ms->state == HEREDOC)
		quote = '<';
	if (ms->state == APPEND)
		quote = '>';
	if (i > 0)
	{
		str_tmp = ft_substr(ms->line, 0, i);
		lst = insertEnd(lst, str_tmp);
		free(str_tmp);
		ms->line = trim_head(ms->line, --i);
	}
	while (ms->line[i] && ms->line[i] == quote)
		++i;
	str_tmp = ft_substr(ms->line, 0, i);
	lst = insertEnd(lst, str_tmp);
	/*if (ms->state == HEREDOC)
		lst = insertEnd(lst, "<<");
	else if (ms->state == APPEND)
		lst = insertEnd(lst, ">>");*/
	ms->line = trim_head(ms->line, i);
	*index = 0;
	return (lst);
}

void	ft_lexer(t_msh *ms)
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
			lst = token_space(ms, lst, &i);
		else if (ms->state == PIPE)
			lst = token_pipe(ms, lst, &i);
		else if (ms->state == S_QUOTE || ms->state == D_QUOTE)
			lst = token_quote(ms, lst, &i);
		else if (ms->state == REDIRECT_I || ms->state == REDIRECT_O)
			lst = token_redirect(ms, lst, &i);
		else if (ms->state == HEREDOC || ms->state == APPEND)
			lst = token_double_arrow(ms, lst, &i);
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
