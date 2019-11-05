/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_prime.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 22:29:19 by blanna            #+#    #+#             */
/*   Updated: 2019/09/11 19:12:57 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"
#include "error.h"

static int	is_prime(int num)
{
	int	i;

	if (num == 1)
		return (0);
	i = 2;
	while (i * i <= num)
	{
		if (i < 0)
		{
			error();
			exit(1);
		}
		if (num % i == 0)
			return (0);
		i++;
	}
	return (1);
}

uint32_t	get_next_prime(int64_t num)
{
	while (1)
	{
		if (num < 0)
		{
			error();
			exit(1);
		}
		if (is_prime(++num))
			return (num);
	}
}

int			is_valid_number(char *s)
{
	if (*s == '+')
		++s;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		++s;
	}
	return (1);
}
