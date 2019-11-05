/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:40:29 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:46:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLUTION_H
# define SOLUTION_H

# include "libft.h"

/*
**	Contains the data necessary to solve the problem & output the solution
*/

/*
**	Each ant is represented by its id and by a pointer to one of the points
**	in the path (from which it will be easy to get the next one using
**	pointer arithmetics).
*/

typedef struct	s_ant
{
	uint32_t	*node;
	char		*name;
}				t_ant;

/*
**	Paths are represented by an array of pointers to arrays of integers.
**	paths[0] contains the first path and paths[n_paths - 1] has the last one.
**	paths[x][0] contains the number of nodes in the path.
**	each array paths[x] has paths[x][0] + 1 elements.
**	-
**	paths is sorted by the number of nodes
*/

typedef struct	s_solution
{
	uint32_t	n_ants;
	uint32_t	start;
	uint32_t	end;
	uint32_t	n_paths;
	uint32_t	turns;
	uint32_t	**paths;
	t_ant		*ants;
	uint32_t	*ants_per_path;
}				t_solution;

#endif
