/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:00 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:00 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_SOLUTION_INTERNAL_H
# define FIND_SOLUTION_INTERNAL_H

# include "find_solution.h"

# include "graph_customisation.h"

/*
**	Using signed values to signal INFINITY and UNDEFINED as -1
*/

typedef struct	s_dijdata
{
	int64_t	dist;
	int64_t	prev;
	int		visited;
}				t_dijdata;

/*
**	The function returns a path array containing the shortest path between
**	source and sink in indices [1...n] and the number of nodes in it at index 0.
**
**	If no path has been found, the function return a NULL pointer.
*/

uint32_t		*dijkstra(t_graph *res, uint32_t source,
		uint32_t sink, uint8_t *visited);

/*
**	Dijkstra's helper function. Updates the vertices that dijkstra searches.
*/

void			update_distances(t_graph *res, uint32_t item, t_htab *v,
		uint8_t *visited);

/*
**	Sends maximum flow in the graph g along the augmenting path path, using
**	the residual graph res to calculate the bottleneck value.
*/

uint32_t		update_flow(t_graph *g, t_graph *res, uint32_t *path);

/*
**	Specific graph operations.
*/

t_graph			*copy_nodes(t_graph *g);
t_graph			*build_residual_graph(t_graph *g);
void			update_residual_graph(t_graph *g, t_graph *res, uint32_t *path);

/*
**	Helper function to pass on to ft_lstfind and ft_lstdelif.
*/

int				is_edge_to(t_list *elem, void *data);

/*
**	Manages arrays of paths (see solution.h)
**	UPD: del_paths moved to find_solution.h, as it is accessed from main.c
*/

uint32_t		**build_paths(t_graph *g, uint32_t n_paths, t_solution *sol);

/*
**	Calculates the number of turns needed by the algorithm to pass all the ants.
*/

uint32_t		get_turns(uint32_t **paths, uint32_t n_paths, uint32_t n_ants);

#endif
