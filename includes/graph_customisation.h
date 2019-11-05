/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_customisation.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:40:29 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:40:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_CUSTOMISATION_H
# define GRAPH_CUSTOMISATION_H

# include "libft.h"

/*
**	In t_edge the value of sink should be first for compatibility with libft
*/

typedef struct	s_edge
{
	uint32_t	sink;
	int			capacity;
	int			cost;
	int			flow;
}				t_edge;

#endif
