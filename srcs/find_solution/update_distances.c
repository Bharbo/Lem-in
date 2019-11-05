/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_distances.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:05:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 15:05:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static void		update_vertex(t_dijdata *vertex, t_dijdata *alt_vertex,
		t_list *current_edge, uint8_t *visited)
{
	int	neg_edge;

	neg_edge = ((t_edge *)current_edge->content)->cost < 0;
	if ((vertex->visited == 0 || neg_edge)
		&& (vertex->dist < 0 || alt_vertex->dist <= vertex->dist))
	{
		vertex->dist = alt_vertex->dist;
		vertex->prev = alt_vertex->prev;
		if (neg_edge)
		{
			vertex->visited = 0;
			visited[((t_edge *)current_edge->content)->sink] = 0;
		}
	}
}

void			update_distances(t_graph *res, uint32_t item, t_htab *v,
		uint8_t *visited)
{
	t_list		*current;
	int64_t		dist_to_item;
	t_dijdata	*vertex;
	int64_t		altdist;

	if (!res || !v)
		return ;
	current = res->items[item]->value;
	dist_to_item = ((t_dijdata *)v->items[item]->value)->dist;
	while (current)
	{
		vertex = v->items[((t_edge *)current->content)->sink]->value;
		altdist = dist_to_item + ((t_edge *)current->content)->cost;
		if (!visited[item] || ((t_edge *)current->content)->cost < 0)
			update_vertex(vertex, &(t_dijdata){altdist, item, 0},
					current, visited);
		current = current->next;
	}
}
