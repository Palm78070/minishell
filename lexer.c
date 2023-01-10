/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/10 19:47:04 by rath             ###   ########.fr       */
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

int	is_double_arrow(char *s, int i)
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
		return (SPACE);
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
		else if (ms->state == HEREDOC || ms->state == APPEND
			|| ms->state == AND_IF || ms->state == OR_IF)
			lst = token_double_sign(ms, lst, &i);
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
