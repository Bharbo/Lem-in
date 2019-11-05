/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_turns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:51:14 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static uint32_t	get_max_edges(uint32_t **paths, uint32_t n_paths)
{
	uint32_t	i;
	uint32_t	out;

	i = 0;
	out = 0;
	while (i < n_paths)
	{
		if (paths[i][0] > out)
			out = paths[i][0];
		++i;
	}
	return (out ? out - 1 : 0);
}

/*
**	The function returns the number of turns that are needed
**	if ALL the paths are used.
*/

uint32_t		get_turns(uint32_t **paths, uint32_t n_paths, uint32_t n_ants)
{
	uint32_t	i;
	uint32_t	max_edges;
	uint32_t	ants_buildup;
	uint32_t	extra_step;

	if (!paths || !n_paths || !n_ants)
		return (0);
	max_edges = get_max_edges(paths, n_paths);
	i = 0;
	ants_buildup = 0;
	while (i < n_paths)
	{
		ants_buildup += max_edges - (paths[i][0] - 1) + 1;
		++i;
	}
	if (ants_buildup > n_ants)
		return (max_edges);
	extra_step = ((n_ants - ants_buildup) % n_paths) ? 1 : 0;
	return (max_edges + ((n_ants - ants_buildup) / n_paths) + extra_step);
}
