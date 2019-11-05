/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:41:04 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 22:41:05 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"
#include "error.h"

int64_t	new_room(t_graph *g, char *name)
{
	long		size;
	int64_t		hash;

	if (name[0] == '#' || (size = ft_strfind(name, ' ')) == -1)
	{
		errno = EINVALIDROOM;
		return (-1);
	}
	if (ft_graphget(g, name, (uint32_t)size) != -1)
	{
		errno = EDUPLICATEROOM;
		return (-1);
	}
	if ((hash = ft_graphadd(g, name, (uint32_t)size)) == -1)
	{
		errno = EMEMORY;
		return (-1);
	}
	return (hash);
}
