/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

t_graph	*copy_nodes(t_graph *g)
{
	t_graph		*out;
	t_hash_item	*item;
	uint32_t	i;

	if (!g || !(out = ft_graphnew(g->size)))
		return (NULL);
	i = 0;
	while (i < g->size)
	{
		if (g->items[i] == NULL || g->items[i] == DELETED_HI)
			out->items[i] = g->items[i];
		else if (!(item =
				ft_hilnew(g->items[i]->key, g->items[i]->ksize, NULL, 0)))
		{
			ft_graphdel(&out);
			return (NULL);
		}
		else
			out->items[i] = item;
		++i;
	}
	return (out);
}
