/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:35 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:50:16 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output_internal.h"

static uint32_t	get_uint_len(uint32_t n)
{
	uint32_t	out;

	out = n == 0;
	while (n != 0)
	{
		n /= 10;
		out++;
	}
	return (out);
}

static char		*get_ant_name(uint32_t n)
{
	uint32_t	len;
	char		*out;

	len = get_uint_len(n);
	if (!(out = (char *)malloc(len + 3)))
		return (NULL);
	out[0] = 'L';
	out[len + 1] = '-';
	out[len + 2] = '\0';
	if (!n)
		out[1] = 0;
	while (n != 0)
	{
		out[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (out);
}

t_ant			*build_ants(t_solution *sol)
{
	t_ant		*out;
	uint32_t	i;

	if (!sol || !(out = (t_ant *)malloc(sol->n_ants * sizeof(t_ant))))
		return (NULL);
	i = 0;
	while (i < sol->n_ants)
	{
		out[i].node = NULL;
		if (!(out[i].name = get_ant_name(i + 1)))
		{
			del_ants(&out, i);
			return (NULL);
		}
		++i;
	}
	return (out);
}
