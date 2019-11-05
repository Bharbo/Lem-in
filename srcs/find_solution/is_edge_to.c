/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_edge_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

int	is_edge_to(t_list *elem, void *data)
{
	if (!elem || !elem->content || !data)
		return (0);
	return (((t_edge *)elem->content)->sink == *((uint32_t *)data));
}
