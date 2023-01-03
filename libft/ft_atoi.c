/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 20:08:40 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/11 21:20:36 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_instr(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		++s;
	}
	return (0);
}

static int	ft_isspace(char c)
{
	return (is_instr(c, " \t\r\n\v\f"));
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		++str;
	if (*str != '\0' && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str && ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0');
		if (result > LLONG_MAX && sign > 0)
			return (-1);
		else if (result > LLONG_MAX)
			return (0);
		++str;
	}
	return ((int)(result * sign));
}
