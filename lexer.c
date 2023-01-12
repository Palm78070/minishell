/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/12 12:25:33 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ms->state == SP)
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
		lst = insert_str(ms, lst, i);
	print_list(lst);
	free_list(lst);
}
