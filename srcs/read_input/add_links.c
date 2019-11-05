/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:06:00 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:11:11 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"
#include "error.h"

static int	graph_add_uedge(t_graph *g,
		int64_t source, int64_t sink, t_edge *edge)
{
	t_list	*value;
	t_list	*newlst;

	if (!edge || source < 0 || sink < 0)
		return (-1);
	value = g->items[source]->value;
	if (!(newlst = ft_lstnew(edge, sizeof(t_edge))))
	{
		errno = EMEMORY;
		return (-1);
	}
	ft_lstadd(&value, newlst);
	((t_edge *)value->content)->sink = sink;
	g->items[source]->value = value;
	value = g->items[sink]->value;
	if (!(newlst = ft_lstnew(edge, sizeof(t_edge))))
	{
		errno = EMEMORY;
		return (-1);
	}
	ft_lstadd(&value, newlst);
	((t_edge *)value->content)->sink = source;
	g->items[sink]->value = value;
	return (0);
}

static int	find_source_sink(t_graph *g, char *line,
		int64_t *source, int64_t *sink)
{
	uint32_t	i;

	i = 0;
	while (line[i] != '-')
		++i;
	*source = ft_graphget(g, line, i);
	*sink = ft_graphget(g, line + i + 1, ft_strlen(line + i + 1));
	if (*source == -1 || *sink == -1)
	{
		errno = EINVALIDROOM;
		return (-1);
	}
	if (ft_graphhas_edge(g, *source, *sink))
	{
		errno = EDUPLICATELINK;
		return (-1);
	}
	return (0);
}

static int	check_comment(char *line)
{
	if (line[0] != '#')
		return (LINE_OK);
	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return (LINE_INVALID);
	return (LINE_COMMENT);
}

int			add_links(t_graph *g, t_list *lst)
{
	int64_t				src;
	int64_t				sink;
	enum e_line_status	status;

	while (lst)
	{
		if ((status = check_comment(lst->content)) == LINE_INVALID)
			return (-1);
		if (status == LINE_OK
				&& (find_source_sink(g, lst->content, &src, &sink) == -1
				|| graph_add_uedge(g, src, sink, &(t_edge){0, 1, 1, 0}) == -1))
			return (-1);
		lst = lst->next;
	}
	return (0);
}
