/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_update_residual_graph.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:51:56 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static void	process_edge(t_graph *out, uint32_t source, t_edge *edge)
{
	t_list	*nodes;

	if (edge->flow < edge->capacity)
	{
		nodes = out->items[source]->value;
		ft_lstadd(&nodes, ft_lstnew(&(t_edge){edge->sink, edge->capacity,
				edge->cost, edge->capacity - edge->flow}, sizeof(t_edge)));
		out->items[source]->value = nodes;
	}
	if (edge->flow)
	{
		nodes = out->items[edge->sink]->value;
		ft_lstadd(&nodes, ft_lstnew(&(t_edge){source, 0,
				-edge->cost, -edge->flow}, sizeof(t_edge)));
		out->items[edge->sink]->value = nodes;
	}
}

t_graph		*build_residual_graph(t_graph *g)
{
	t_graph		*out;
	t_list		*current;
	uint32_t	i;

	if (!(out = copy_nodes(g)))
		return (NULL);
	i = 0;
	while (i < g->size)
	{
		if (g->items[i] != NULL && g->items[i] != DELETED_HI)
		{
			current = g->items[i]->value;
			while (current)
			{
				if (current->content)
					process_edge(out, i, current->content);
				current = current->next;
			}
		}
		++i;
	}
	return (out);
}

void		update_residual_graph(t_graph *g, t_graph *res, uint32_t *path)
{
	uint32_t	i;
	t_list		*current;
	uint32_t	source;
	uint32_t	sink;

	i = 1;
	while (i < path[0])
	{
		source = path[i];
		sink = path[i + 1];
		current = res->items[source]->value;
		ft_lstdelif(&current, is_edge_to, &sink, ft_delcontent);
		res->items[source]->value = current;
		current = res->items[sink]->value;
		ft_lstdelif(&current, is_edge_to, &source, ft_delcontent);
		res->items[sink]->value = current;
		process_edge(res, source, ft_lstfind(g->items[source]->value,
				is_edge_to, &sink)->content);
		process_edge(res, sink, ft_lstfind(g->items[sink]->value,
				is_edge_to, &source)->content);
		++i;
	}
}
