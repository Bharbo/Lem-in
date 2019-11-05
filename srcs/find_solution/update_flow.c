/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_flow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static t_list	*get_minimum_cost_edge(t_list *lst, uint32_t sink)
{
	t_list	*edge;
	t_list	*new_edge;

	if (!lst)
		return (NULL);
	edge = ft_lstfind(lst, is_edge_to, &sink);
	if (((t_edge *)edge->content)->cost < 0)
		return (edge);
	if ((new_edge = ft_lstfind(edge->next, is_edge_to, &sink)))
		return (new_edge);
	return (edge);
}

static int		get_bottleneck(t_graph *res, uint32_t *path)
{
	int			out;
	uint32_t	i;
	t_list		*edge;
	int			current_bottleneck;

	out = -1;
	i = 1;
	while (i < path[0])
	{
		edge = get_minimum_cost_edge(res->items[path[i]]->value, path[i + 1]);
		current_bottleneck = ((t_edge *)edge->content)->flow;
		if (current_bottleneck < 0)
			current_bottleneck *= -1;
		if (out < 0 || current_bottleneck < out)
			out = current_bottleneck;
		++i;
	}
	return (out);
}

uint32_t		update_flow(t_graph *g, t_graph *res, uint32_t *path)
{
	int			increase;
	uint32_t	i;
	t_list		*edge;
	t_list		*inv;

	increase = get_bottleneck(res, path);
	i = 1;
	while (i < path[0])
	{
		edge = ft_lstfind(g->items[path[i]]->value, is_edge_to, &path[i + 1]);
		inv = ft_lstfind(g->items[path[i + 1]]->value, is_edge_to, &path[i]);
		if (inv && ((t_edge *)inv->content)->flow)
			((t_edge *)inv->content)->flow -= increase;
		else
			((t_edge *)edge->content)->flow += increase;
		++i;
	}
	return (increase);
}
