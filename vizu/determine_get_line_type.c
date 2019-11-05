/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_get_line_type.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

int	determine_line_type(char *line)
{
	if (!line[0])
		return (LT_SKIPPABLE);
	if (line[0] == 'L')
		return (LT_TURN);
	if (line[0] == '#')
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			return (LT_COMMAND);
		return (LT_SKIPPABLE);
	}
	if (ft_strfind(line, ' ') != -1)
		return (LT_ROOM);
	if (ft_strfind(line, '-') != -1)
		return (LT_LINK);
	return (LT_ANTS);
}

int	line_type(t_list *lst)
{
	return ((int)lst->content_size);
}
