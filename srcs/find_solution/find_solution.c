/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

static void	sort_paths(uint32_t **paths, uint32_t size)
{
	uint32_t	i;
	uint32_t	sorted;
	uint32_t	*current_min;
	uint32_t	current_argmin;

	sorted = 0;
	while (sorted < size)
	{
		current_min = paths[sorted];
		current_argmin = sorted;
		i = sorted + 1;
		while (i < size)
		{
			if (paths[i][0] < current_min[0])
			{
				current_argmin = i;
				current_min = paths[i];
			}
			++i;
		}
		paths[current_argmin] = paths[sorted];
		paths[sorted] = current_min;
		++sorted;
	}
}

static int	is_better(t_graph *g, t_graph *res, t_solution *sol,
		uint32_t *augm_path)
{
	uint32_t	**paths;
	uint32_t	new_turns;

	update_flow(g, res, augm_path);
	if (!(paths = build_paths(g, sol->n_paths + 1, sol)))
		return (0);
	if ((new_turns = get_turns(paths, sol->n_paths + 1, sol->n_ants))
		>= sol->turns && sol->turns)
	{
		del_paths(&paths, sol->n_paths + 1);
		return (0);
	}
	sol->turns = new_turns;
	del_paths(&sol->paths, sol->n_paths);
	sol->paths = paths;
	(sol->n_paths)++;
	return (1);
}

static void	update_visited(uint8_t *visited, uint32_t visized_size,
		uint32_t **paths, uint32_t n_paths)
{
	uint32_t	i;
	uint32_t	j;

	if (!n_paths || !paths || !visited)
		return ;
	ft_memset(visited, 0, visized_size);
	i = 0;
	while (i < n_paths)
	{
		j = 2;
		while (j < paths[i][0])
		{
			visited[paths[i][j]] = 1;
			++j;
		}
		++i;
	}
}

void		find_solution(t_graph *g, t_solution *sol)
{
	t_graph		*res;
	uint32_t	*augm_path;
	uint8_t		*visited;

	if (!g || !sol || !sol->n_ants || !(res = build_residual_graph(g)))
		return ;
	if (!(visited = ft_memalloc(g->size)))
	{
		ft_graphdel(&res);
		return ;
	}
	while ((augm_path = dijkstra(res, sol->start, sol->end, visited)))
	{
		if (!is_better(g, res, sol, augm_path))
		{
			free(augm_path);
			break ;
		}
		update_residual_graph(g, res, augm_path);
		free(augm_path);
		update_visited(visited, g->size, sol->paths, sol->n_paths);
	}
	free(visited);
	ft_graphdel(&res);
	sort_paths(sol->paths, sol->n_paths);
}
