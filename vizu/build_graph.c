/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:51 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:51 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static t_hash_item	*new_room(char *line)
{
	t_coords	coords;
	size_t		length;

	length = ft_strfind(line, ' ');
	coords.x = ft_atoi(line + length);
	coords.y = ft_atoi(ft_strchr(line + length + 1, ' '));
	return (ft_hinew(line, length, &coords, sizeof(coords)));
}

static int64_t		add_room_to_graph(t_viz_data *vdata)
{
	t_hash_item	*newroom;
	int64_t		hash;

	if (!(newroom = new_room(vdata->current_line->content)))
		return (-1);
	if ((hash = ft_htadd(vdata->graph, newroom)) == -1)
	{
		ft_hidel(&newroom);
		return (-1);
	}
	return (hash);
}

static int			add_start_finish(t_viz_data *vdata)
{
	int			is_start;
	int64_t		hash;

	is_start = ft_strequ(vdata->current_line->content, "##start");
	vdata->current_line = vdata->current_line->next;
	if ((hash = add_room_to_graph(vdata)) == -1)
		return (-1);
	if (is_start)
		vdata->start = hash;
	else
		vdata->end = hash;
	return (0);
}

static int			add_links(t_viz_data *vdata)
{
	t_list	*newlst;
	t_link	link;
	size_t	hyphen_id;
	char	*line;

	while (vdata->current_line && line_type(vdata->current_line) == LT_LINK)
	{
		line = vdata->current_line->content;
		hyphen_id = ft_strfind(line, '-');
		link.source = ft_htgetid(vdata->graph, line, hyphen_id);
		link.sink = ft_htgetid(vdata->graph, line + hyphen_id + 1,
				ft_strlen(line + hyphen_id + 1));
		if (!(newlst = ft_lstnew(&link, sizeof(link))))
			return (-1);
		ft_lstadd(&vdata->links, newlst);
		vdata->current_line = vdata->current_line->next;
	}
	return (0);
}

int					build_graph(t_viz_data *vdata)
{
	if (!vdata || !vdata->n_rooms || !vdata->lines
			|| !(vdata->graph = ft_graphnew(MAX_NODES)))
		return (-1);
	vdata->n_ants = ft_atoi(vdata->current_line->content);
	vdata->current_line = vdata->current_line->next;
	while (vdata->current_line && (line_type(vdata->current_line) == LT_ROOM
			|| line_type(vdata->current_line) == LT_COMMAND))
	{
		if (line_type(vdata->current_line) == LT_COMMAND)
		{
			if (add_start_finish(vdata) == -1)
				return (-1);
		}
		else if (add_room_to_graph(vdata) == -1)
			return (-1);
		vdata->current_line = vdata->current_line->next;
	}
	return (add_links(vdata));
}
