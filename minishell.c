/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/03 22:08:16 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh *ms;

int is_exit(char *s)
{
 if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't')
 {
		printf("exit\n");
		return (1);
 }
 return (0);
}

/*int	is_quit(char *s)
{
 if (is_exit(s) || is_sigquit(s))
		return (1);
 return (0);
}*/

void ft_handler(int signum)
{
 if (signum == SIGQUIT)
 {
		// ft_clear(ms);
		// exit(1);
		return;
 }
}

int main(void)
{
 ms = (t_msh *)malloc(sizeof(t_msh));
 if (!ms)
		ft_error("Fail to malloc struct", ms);
 // sigemptyset(&ms->sa.sa_mask);
 // sigaddset(&ms->sa.sa_mask, SIGQUIT);
 // ms->sa.sa_handler = ft_handler;
 // sigaction(SIGQUIT, &ms->sa, 0);
 ms->line = "\0";
 while (ms->line != NULL)
 {
		ms->line = rl_get(ms);
		if (is_exit(ms->line))
			break;
		printf("input from readline %s\n", ms->line);
		ft_token(ms->line);
 }
 ft_clear(ms);
 return (0);
}
