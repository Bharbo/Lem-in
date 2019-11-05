/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_step.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static void	output_frame(struct winsize *ws, char *img)
{
	int y;
	int x;

	y = -1;
	while (++y < ws->ws_row)
	{
		x = -1;
		while (++x < ws->ws_col)
		{
			if (img[y * ws->ws_col + x] == PIX_ANT)
				mvprintw(y, x, "%s", UTF_ANT);
			else if (img[y * ws->ws_col + x] == PIX_ROOM)
				mvprintw(y, x, "%s", UTF_ROOM);
			else if (img[y * ws->ws_col + x] == PIX_LINK)
				mvprintw(y, x, "%s", UTF_LINK);
			else if (img[y * ws->ws_col + x] == PIX_START)
				mvprintw(y, x, "%s", UTF_START);
			else if (img[y * ws->ws_col + x] == PIX_END)
				mvprintw(y, x, "%s", UTF_END);
			else
				mvprintw(y, x, "%c", ' ');
		}
	}
	refresh();
	usleep(5000);
}

static void	draw_rooms(t_viz_data *vdata)
{
	uint32_t	i;
	t_coords	*coords;
	t_graph		*g;

	g = vdata->graph;
	i = 0;
	while (i < g->size)
	{
		if (g->items[i] == NULL || g->items[i] == DELETED_HI)
		{
			++i;
			continue;
		}
		coords = g->items[i]->value;
		vdata->img[coords->y * vdata->ws.ws_col + coords->x] = PIX_ROOM;
		++i;
	}
	coords = g->items[vdata->start]->value;
	vdata->img[coords->y * vdata->ws.ws_col + coords->x] = PIX_START;
	coords = g->items[vdata->end]->value;
	vdata->img[coords->y * vdata->ws.ws_col + coords->x] = PIX_END;
}

static void	draw_links(t_viz_data *vdata)
{
	t_list	*current;
	t_link	*link;
	t_htab	*g;

	g = vdata->graph;
	current = vdata->links;
	while (current)
	{
		link = current->content;
		draw_line(vdata, g->items[link->source]->value,
				g->items[link->sink]->value);
		current = current->next;
	}
}

void		output_step(t_viz_data *vdata, t_list *ants)
{
	t_ant		*ant;
	t_coords	p;

	ft_memset(vdata->img, PIX_EMPTY, vdata->ws.ws_col * vdata->ws.ws_row);
	draw_links(vdata);
	draw_rooms(vdata);
	while (ants)
	{
		ant = ants->content;
		ant->iter += (float)ant->len_path / (float)LEN_TURN;
		if ((uint32_t)ant->iter < ant->len_path)
		{
			p = ant->path[(uint32_t)ant->iter];
			vdata->img[p.y * vdata->ws.ws_col + p.x] = PIX_ANT;
		}
		ants = ants->next;
	}
	output_frame(&vdata->ws, vdata->img);
}
