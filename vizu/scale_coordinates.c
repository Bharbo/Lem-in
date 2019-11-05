/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static t_coords	get_max_coords(t_viz_data *vdata)
{
	uint32_t	i;
	t_coords	max_coords;
	t_hash_item	*node;

	i = 0;
	max_coords = (t_coords){0, 0};
	while (i < vdata->graph->size)
	{
		node = vdata->graph->items[i];
		if (node != NULL && node != DELETED_HI)
		{
			if (((t_coords *)node->value)->x > max_coords.x)
				max_coords.x = ((t_coords *)node->value)->x;
			if (((t_coords *)node->value)->y > max_coords.y)
				max_coords.y = ((t_coords *)node->value)->y;
		}
		++i;
	}
	return (max_coords);
}

static int		scale(t_viz_data *vdata, t_coords factor)
{
	uint32_t	i;
	t_coords	new_p;
	t_coords	old_p;
	t_hash_item	*node;

	i = 0;
	while (i < vdata->graph->size)
	{
		node = vdata->graph->items[i];
		if (node != NULL && node != DELETED_HI)
		{
			old_p = *((t_coords *)node->value);
			new_p = (t_coords){old_p.x / factor.x, old_p.y / factor.y};
			if (vdata->img[new_p.y * vdata->ws.ws_col + new_p.x])
				return (-1);
			vdata->img[new_p.y * vdata->ws.ws_col + new_p.x] = 1;
			ft_memcpy(node->value, &new_p, sizeof(t_coords));
		}
		++i;
	}
	return (0);
}

int				scale_coordinates(t_viz_data *vdata)
{
	t_coords	max_coords;
	t_coords	scaling_factor;
	t_coords	window_size;

	max_coords = get_max_coords(vdata);
	scaling_factor = (t_coords){1, 1};
	window_size = (t_coords){vdata->ws.ws_col, vdata->ws.ws_row};
	window_size.x -= window_size.x / BORDER_PROPORTION;
	window_size.y -= window_size.y / BORDER_PROPORTION;
	if (max_coords.x > window_size.x)
		scaling_factor.x = (max_coords.x > window_size.x * 2) ?
				(max_coords.x / window_size.x + 1) : 2;
	if (max_coords.y > window_size.y)
		scaling_factor.y = (max_coords.y > window_size.y * 2) ?
				(max_coords.y / window_size.y + 1) : 2;
	return (scale(vdata, scaling_factor));
}
