/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:40:29 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:40:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_SOLUTION_H
# define FIND_SOLUTION_H

# include "libft.h"

# include "solution.h"

/*
**	The function finds the paths best for the given graph and number of ants.
*/

void			find_solution(t_graph *g, t_solution *sol);

/*
**	Performs memory clean.
*/

void			del_paths(uint32_t ***paths, uint32_t n_paths);

#endif
