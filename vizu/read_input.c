/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static int	build_ants(t_viz_data *vdata)
{
	uint32_t	i;

	if (!(vdata->ants = malloc(sizeof(uint32_t) * (vdata->n_ants + 1))))
		return (-1);
	i = 0;
	while (i <= vdata->n_ants)
	{
		vdata->ants[i] = vdata->start;
		++i;
	}
	return (0);
}

int			read_input(t_viz_data *vdata)
{
	if (ioctl(1, TIOCGWINSZ, &vdata->ws) == -1
		|| read_lines(vdata) == -1 || build_graph(vdata) == -1
		|| !(vdata->img = ft_memalloc(vdata->ws.ws_col * vdata->ws.ws_row))
		|| build_ants(vdata) == -1)
		return (-1);
	return (0);
}
