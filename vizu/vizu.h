/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 15:45:41 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZU_H
# define VIZU_H

# include <locale.h>
# include <ncurses.h>
# include <sys/ioctl.h>
# include <unistd.h>

# include "libft.h"

# define MAX_NODES 127
# define LEN_TURN 255
# define BORDER_PROPORTION 10

/*
**	((char []){0xF0, 0x9F, 0x98, 0x82}) // tears of joy
**	((char []){0xF0, 0x9F, 0x8C, 0x9A}) // black moon
**	((char []){0xF0, 0x9F, 0x90, 0x9C, 0x0}) // ant
**	((char []){0xE2, 0x9C, 0xA1, 0x00}) // david's star
**	((char []){0xF0, 0x93, 0x82, 0xB8, 0x00}) // egyptian penis
*/

# define UTF_ANT ((char []){0xE2, 0x98, 0xB9, 0x00})
# define UTF_LINK ((char []){0xE2, 0x8B, 0x85, 0x00})
# define UTF_ROOM ((char []){0xE2, 0x98, 0x89, 0x00})
# define UTF_START "$"
# define UTF_END ((char []){0xE2, 0x98, 0xAD, 0x00})

# define PIX_EMPTY ' '
# define PIX_ROOM 'X'
# define PIX_START 'S'
# define PIX_END 'E'
# define PIX_LINK '.'
# define PIX_ANT '*'

typedef struct	s_coords
{
	uint16_t	x;
	uint16_t	y;
}				t_coords;

typedef struct	s_link
{
	uint32_t	source;
	uint32_t	sink;
}				t_link;

typedef struct	s_viz_data
{
	struct winsize	ws;
	char			*img;
	t_list			*lines;
	t_list			*current_line;
	t_htab			*graph;
	uint8_t			n_rooms;
	uint32_t		n_ants;
	uint32_t		*ants;
	uint32_t		start;
	uint32_t		end;
	t_list			*links;
}				t_viz_data;

typedef struct	s_ant
{
	uint32_t	id;
	float		iter;
	size_t		len_path;
	t_coords	*path;
}				t_ant;

typedef struct	s_draw_line_params
{
	int	dx;
	int	dy;
	int	incr;
	int delta;
}				t_draw_line_params;

enum			e_line_type
{
	LT_ROOM,
	LT_COMMAND,
	LT_SKIPPABLE,
	LT_LINK,
	LT_TURN,
	LT_ANTS
};

int				read_input(t_viz_data *vdata);
int				read_lines(t_viz_data *vdata);
int				build_graph(t_viz_data *vdata);

int				determine_line_type(char *line);
int				line_type(t_list *lst);

int				get_next_move(t_viz_data *vdata);
size_t			build_line(t_coords **path, t_coords *source, t_coords *sink);

void			output_step(t_viz_data *vdata, t_list *ants);
void			draw_line(t_viz_data *vdata, t_coords *source, t_coords *sink);

int				clear_vdata(t_viz_data *vdata, int return_code);
void			del_ant(t_ant *ant);
void			del_ant_content(void **content, size_t *size);

int				scale_coordinates(t_viz_data *vdata);

int				ft_abs(int n);

#endif
