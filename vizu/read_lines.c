/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static void	add_line(t_viz_data *vdata, t_list *newlst)
{
	if (!vdata->lines)
	{
		vdata->current_line = newlst;
		vdata->lines = vdata->current_line;
	}
	else
		vdata->current_line = ft_lstappend(vdata->current_line, newlst);
}

int			read_lines(t_viz_data *vdata)
{
	char	*line;
	t_list	*newlst;
	int		line_type;

	while (ft_gnl(0, &line) > 0)
	{
		if ((line_type = determine_line_type(line)) == LT_SKIPPABLE)
		{
			free(line);
			continue ;
		}
		if (!(newlst = ft_lstnewlink(line, line_type)))
		{
			free(line);
			return (-1);
		}
		add_line(vdata, newlst);
		vdata->n_rooms += (line_type == LT_ROOM);
		if (vdata->n_rooms > MAX_NODES)
			return (-1);
	}
	vdata->current_line = vdata->lines;
	return (0);
}
