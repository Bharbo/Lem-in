/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static void	draw_line_low(t_viz_data *vdata, t_coords *source, t_coords *sink)
{
	int			dx;
	int			dy;
	int			y_incr;
	int			delta;
	t_coords	p;

	dx = sink->x - source->x;
	dy = sink->y - source->y;
	y_incr = (dy >= 0) - (dy < 0);
	dy *= (dy >= 0) - (dy < 0);
	delta = 2 * dy - dx;
	p = *source;
	while (p.x != sink->x)
	{
		vdata->img[p.y * vdata->ws.ws_col + p.x] = PIX_LINK;
		if (delta > 0)
		{
			p.y += y_incr;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		++(p.x);
	}
}

static void	draw_line_high(t_viz_data *vdata, t_coords *source, t_coords *sink)
{
	int			dx;
	int			dy;
	int			x_incr;
	int			delta;
	t_coords	p;

	dx = sink->x - source->x;
	dy = sink->y - source->y;
	x_incr = (dx >= 0) - (dx < 0);
	dx *= (dx >= 0) - (dx < 0);
	delta = 2 * dx - dy;
	p = *source;
	while (p.y != sink->y)
	{
		vdata->img[p.y * vdata->ws.ws_col + p.x] = PIX_LINK;
		if (delta > 0)
		{
			p.x += x_incr;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		++(p.y);
	}
}

void		draw_line(t_viz_data *vdata, t_coords *source, t_coords *sink)
{
	if (ft_abs(sink->y - source->y) < ft_abs(sink->x - source->x))
	{
		if (source->x > sink->x)
			draw_line_low(vdata, sink, source);
		else
			draw_line_low(vdata, source, sink);
	}
	else
	{
		if (source->y > sink->y)
			draw_line_high(vdata, sink, source);
		else
			draw_line_high(vdata, source, sink);
	}
}
