/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/04 22:00:31 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_head(char *s, int delim_indx)
{
	int i = delim_indx;
	int len = ft_strlen(s) - delim_indx;
	char *res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (s[++i])
		res[i] = s[i];
	res[i] = '\0';
	free(s);
	return (res);
}

void	ft_token(char *s)
{
	int i;
	t_lst	*lst;

	i = 0;
	lst = NULL;
	while (s[i])
	{
		if (isspace(s[i]))
		{
			if (i > 0)
			{
				str_tmp = ft_substr(s, 0, i);
				lst = insertEnd(lst, str_tmp);
				free(str_tmp);
			}
			s = trim_head(s, i);
			i = 0;
		}
		if (s[i] == '|')
		{
			if (i > 0)
			{
				str_tmp = ft_substr(s, 0, i);
				lst = insertEnd(lst, str_tmp);
			}
			lst = insertEnd(lst, "|");
			s = trim_head(s, i);
			i = 0;
		}
	}
	print_list(lst);
	free_list(lst);
}
