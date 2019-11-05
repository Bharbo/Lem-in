/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:00 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:00 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_INPUT_INTERNAL_H
# define READ_INPUT_INTERNAL_H

# include "read_input.h"

# include "graph_customisation.h"

typedef struct	s_input_data
{
	uint32_t	n_rooms;
	t_list		*lines;
	uint32_t	has_start : 1;
	uint32_t	has_end : 1;
	uint32_t	has_links : 1;
}				t_input_data;

enum			e_line_type
{
	LINE_TYPE_ROOM,
	LINE_TYPE_LINK,
	LINE_TYPE_INVALID
};

enum			e_line_status
{
	LINE_OK,
	LINE_COMMENT,
	LINE_INVALID
};

enum			e_comment_type
{
	CT_STRT,
	CT_END,
	CT_COMMENT,
	CT_NOCOMMENT,
	CT_ERROR
};

int				check_line(char *line, t_input_data *input);
int				read_lines(t_input_data *input, uint32_t *ants);

uint32_t		get_next_prime(int64_t num);
int				is_valid_number(char *s);

int				build_graph(t_graph *g, t_input_data *inp,
		uint32_t *start, uint32_t *end);

int64_t			new_room(t_graph *g, char *name);

int				add_links(t_graph *g, t_list *lst);

#endif
