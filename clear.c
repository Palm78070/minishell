/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:08:03 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/03 21:04:34 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear(t_msh *ms)
{
	if (ms != NULL)
	{
		if (ms->line != NULL && ms->line[0] != '\0')
			free(ms->line);
	}
}

void	ft_error(char *s, t_msh *ms)
{
	printf("%s\n", s);
	ft_clear(ms);
	exit(EXIT_FAILURE);
}
