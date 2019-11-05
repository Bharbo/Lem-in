/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:06:45 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:12:10 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"
#include "error.h"

static int		handle_hash_sign(t_graph *g, t_list **lst,
		uint32_t *start, uint32_t *end)
{
	t_list				*command;
	int64_t				hash;
	enum e_comment_type	status;

	command = *lst;
	if (!ft_strcmp(command->content, "##start"))
		status = CT_STRT;
	else if (!ft_strcmp(command->content, "##end"))
		status = CT_END;
	else
		return (CT_COMMENT);
	*lst = (*lst)->next;
	if ((hash = new_room(g, (*lst)->content)) == -1)
		return (CT_ERROR);
	if (status == CT_STRT)
		*start = hash;
	else
		*end = hash;
	return (status);
}

static int		handle_start_end_error(t_input_data *input)
{
	if (!input->has_start)
		errno = ENOSTART;
	else if (!input->has_end)
		errno = ENOEND;
	return (-1);
}

static int		skip_to_rooms(t_list **lst)
{
	while (((char *)((*lst)->content))[0] == '#')
	{
		if (!ft_strcmp((*lst)->content, "##start")
				|| !ft_strcmp((*lst)->content, "##end"))
		{
			errno = EINVALIDINPUT;
			return (-1);
		}
		*lst = (*lst)->next;
	}
	(*lst) = (*lst)->next;
	return (0);
}

static void		init_build_graph_data(uint32_t *i, t_list **lst,
		t_input_data *inp)
{
	*i = 0;
	*lst = inp->lines;
	inp->has_start = 0;
	inp->has_end = 0;
}

int				build_graph(t_graph *g, t_input_data *inp,
		uint32_t *start, uint32_t *end)
{
	uint32_t			i;
	t_list				*lst;
	enum e_comment_type	status;

	init_build_graph_data(&i, &lst, inp);
	if (skip_to_rooms(&lst) == -1)
		return (-1);
	while (i < inp->n_rooms)
	{
		status = CT_NOCOMMENT;
		if (((char *)(lst->content))[0] == '#')
		{
			if ((status = handle_hash_sign(g, &lst, start, end)) == CT_ERROR)
				return (-1);
			if (status != CT_COMMENT)
				(status == CT_STRT) ? (++(inp->has_start)) : (++(inp->has_end));
		}
		else if (new_room(g, lst->content) == -1)
			return (-1);
		lst = lst->next;
		i += (status == CT_COMMENT) ? 0 : 1;
	}
	if (!inp->has_start || !inp->has_end)
		return (handle_start_end_error(inp));
	return (add_links(g, lst));
}
