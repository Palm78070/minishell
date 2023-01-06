/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/05 00:43:15 by rath             ###   ########.fr       */
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
	//free(s);
	return (res);
}

t_lst	*ft_token2(char *s, t_lst *lst)
{
	int	i;
	char	*str_tmp;
	//t_lst	*lst;

	i = 0;
	//lst = NULL;
	str_tmp = NULL;
	while (s[i])
	{
		/*if (ft_isspace(s[i]))
		{
			while (s[i] && ft_isspace(s[i]))
				++i;
			if (--i > 0)
			{
				str_tmp = ft_substr(s, 0, i);
				lst = insertEnd(lst, str_tmp);
				free(str_tmp);
			}
			s = trim_head(s, i);
			i = 0;
		}*/
		if (s[i] == '|')
		{
			if (i > 0)
			{
				str_tmp = ft_substr(s, 0, i);
				lst = insertEnd(lst, str_tmp);
				free(str_tmp);
			}
			lst = insertEnd(lst, "|");
			s = trim_head(s, i);
			i = 0;
		}
		else
			++i;
	}
	str_tmp = ft_substr(s, 0, i);
	lst = insertEnd(lst, str_tmp);
	free(str_tmp);
	return (lst);
	//print_list(lst);
	//free_list(lst);
}

void	ft_token(char *s)
{
	char	**sp;
	t_lst	*lst;
	int	i;

	sp = ft_split(s, ' ');
	lst = NULL;
	i = -1;
	while (sp[++i])
	{
		lst = ft_token2(sp[i], lst);
	}
	free_double(sp);
	print_list(lst);
	free_list(lst);
}
