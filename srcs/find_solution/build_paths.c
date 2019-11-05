/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static int		has_nonzero_flow(t_list *elem, void *data)
{
	(void)data;
	return (((t_edge *)elem->content)->flow != 0);
}

static void		fill_path(uint32_t *path, t_varr *varr, t_solution *sol)
{
	uint32_t	idx;

	path[0] = varr->size + 2;
	path[1] = sol->start;
	idx = 2;
	while (idx < varr->size + 2)
	{
		path[idx] = *(uint32_t *)ft_varrget(varr, idx - 2);
		++idx;
	}
	path[idx] = sol->end;
}

static uint32_t	*build_path(t_graph *g, t_list *edges, t_solution *sol)
{
	t_varr		*varr;
	uint32_t	idx;
	uint32_t	*out;

	if (!(varr = ft_varrnew(sizeof(uint32_t))))
		return (NULL);
	while ((idx = ((t_edge *)edges->content)->sink) != sol->end)
	{
		ft_varrappend(varr, &idx);
		if (!(edges = ft_lstfind(g->items[idx]->value, has_nonzero_flow, NULL)))
		{
			ft_varrdel(&varr);
			return (NULL);
		}
	}
	if (!(out = (uint32_t *)malloc(sizeof(uint32_t) * (varr->size + 3))))
	{
		ft_varrdel(&varr);
		return (NULL);
	}
	fill_path(out, varr, sol);
	ft_varrdel(&varr);
	return (out);
}

uint32_t		**build_paths(t_graph *g, uint32_t n_paths, t_solution *sol)
{
	uint32_t	**out;
	t_list		*edges;
	uint32_t	i;

	if (!g || !n_paths || !sol
			|| !(out = (uint32_t **)malloc(sizeof(uint32_t *) * n_paths)))
		return (NULL);
	edges = g->items[sol->start]->value;
	i = 0;
	while (i < n_paths)
	{
		if (!(edges = ft_lstfind(edges, has_nonzero_flow, NULL)))
		{
			del_paths(&out, i);
			return (NULL);
		}
		if (!(out[i] = build_path(g, edges, sol)))
		{
			del_paths(&out, i + 1);
			return (NULL);
		}
		edges = edges->next;
		++i;
	}
	return (out);
}
