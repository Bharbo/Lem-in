/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static size_t	invert(t_coords **path, size_t len)
{
	size_t		i;
	t_coords	temp;

	len = len + 1;
	i = 0;
	while (i < len / 2)
	{
		temp = (*path)[i];
		(*path)[i] = (*path)[len - i - 1];
		(*path)[len - i - 1] = temp;
		++i;
	}
	return (len);
}

static size_t	build_line_low(t_coords **path,
		t_coords *source, t_coords *sink)
{
	t_draw_line_params	params;
	t_coords			p;

	params.dx = sink->x - source->x;
	params.dy = sink->y - source->y;
	params.incr = (params.dy >= 0) - (params.dy < 0);
	params.dy *= (params.dy >= 0) - (params.dy < 0);
	params.delta = 2 * params.dy - params.dx;
	p = *source;
	if (!(*path = (t_coords *)malloc((sink->x - source->x + 1)
			* sizeof(t_coords))))
		return (0);
	while (p.x != sink->x)
	{
		(*path)[p.x - source->x] = p;
		if (params.delta > 0)
		{
			p.y += params.incr;
			params.delta -= 2 * params.dx;
		}
		params.delta += 2 * params.dy;
		++(p.x);
	}
	(*path)[p.x - source->x] = *sink;
	return (sink->x - source->x);
}

static size_t	build_line_high(t_coords **path,
		t_coords *source, t_coords *sink)
{
	t_draw_line_params	params;
	t_coords			p;

	params.dx = sink->x - source->x;
	params.dy = sink->y - source->y;
	params.incr = (params.dx >= 0) - (params.dx < 0);
	params.dx *= (params.dx >= 0) - (params.dx < 0);
	params.delta = 2 * params.dx - params.dy;
	p = *source;
	if (!(*path = (t_coords *)malloc((sink->y - source->y + 1)
			* sizeof(t_coords))))
		return (0);
	while (p.y != sink->y)
	{
		(*path)[p.y - source->y] = p;
		if (params.delta > 0)
		{
			p.x += params.incr;
			params.delta -= 2 * params.dy;
		}
		params.delta += 2 * params.dx;
		++(p.y);
	}
	(*path)[p.y - source->y] = *sink;
	return (sink->y - source->y);
}

size_t			build_line(t_coords **path, t_coords *source, t_coords *sink)
{
	if (ft_abs(sink->y - source->y) < ft_abs(sink->x - source->x))
	{
		if (source->x > sink->x)
			return (invert(path, build_line_low(path, sink, source)));
		else
			return (build_line_low(path, source, sink));
	}
	else
	{
		if (source->y > sink->y)
			return (invert(path, build_line_high(path, sink, source)));
		else
			return (build_line_high(path, source, sink));
	}
}
