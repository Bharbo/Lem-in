/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:52:12 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static t_htab	*djikstra_init(t_graph *res)
{
	t_htab	*out;

	if (!res || !(out = copy_nodes(res)))
		return (NULL);
	if (ft_htset(out, &(t_dijdata){-1, -1, 0}, sizeof(t_dijdata)) == -1)
	{
		ft_htdel(&out, ft_hidel);
		return (NULL);
	}
	return (out);
}

/*
**	Presumes at least one node has non-negative distance, otherwise undefined
*/

static int64_t	pop_min_distance(t_htab *v)
{
	int64_t		min_dist;
	int64_t		min_item;
	uint32_t	i;

	min_dist = -1;
	min_item = -1;
	i = 0;
	while (i < v->size)
	{
		if (v->items[i] != NULL && v->items[i] != DELETED_HI
				&& ((t_dijdata *)v->items[i]->value)->visited == 0
				&& ((t_dijdata *)v->items[i]->value)->dist >= 0
				&& (min_dist == -1
					|| ((t_dijdata *)v->items[i]->value)->dist < min_dist))
		{
			min_dist = ((t_dijdata *)v->items[i]->value)->dist;
			min_item = i;
		}
		++i;
	}
	if (min_dist != -1)
		((t_dijdata *)v->items[min_item]->value)->visited = 1;
	return (min_item);
}

static uint32_t	*construct_path(t_htab *v, uint32_t source, uint32_t sink)
{
	uint32_t	size;
	int64_t		current;
	uint32_t	*out;

	size = 1;
	current = sink;
	while (current != source)
	{
		current = ((t_dijdata *)v->items[current]->value)->prev;
		if (current == -1)
			return (NULL);
		++size;
	}
	out = (uint32_t *)malloc((size + 1) * sizeof(uint32_t));
	if (!out)
		return (NULL);
	out[0] = size;
	current = sink;
	while (size)
	{
		out[size--] = current;
		current = ((t_dijdata *)v->items[current]->value)->prev;
	}
	return (out);
}

uint32_t		*dijkstra(t_graph *res, uint32_t source, uint32_t sink,
		uint8_t *visited)
{
	t_htab		*vertices;
	int64_t		item;
	uint32_t	*path;

	if (!res || source >= res->size || sink >= res->size
			|| res->items[source] == NULL || res->items[source] == DELETED_HI
			|| res->items[sink] == NULL || res->items[sink] == DELETED_HI
			|| !(vertices = djikstra_init(res)))
		return (NULL);
	((t_dijdata *)vertices->items[source]->value)->dist = 0;
	while ((item = pop_min_distance(vertices)) != -1)
	{
		if (item == sink)
			break ;
		update_distances(res, item, vertices, visited);
	}
	path = construct_path(vertices, source, sink);
	ft_htdel(&vertices, ft_hidel);
	return (path);
}
