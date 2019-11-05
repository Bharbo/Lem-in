/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:09:06 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:09:08 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"

static int	check_comment(char *line, t_input_data *input)
{
	if (!ft_strcmp(line, "##start"))
	{
		if (input->has_start)
			return (LINE_INVALID);
		input->has_start = 1;
		return (LINE_OK);
	}
	if (!ft_strcmp(line, "##end"))
	{
		if (input->has_end)
			return (LINE_INVALID);
		input->has_end = 1;
		return (LINE_OK);
	}
	return (LINE_COMMENT);
}

static int	get_line_type(char *s)
{
	int	space_count;

	while (*s && *s != ' ' && *s != '-')
		++s;
	if (!(*s))
		return (LINE_TYPE_INVALID);
	if (*s == ' ')
	{
		space_count = 1;
		while (*(++s))
		{
			if (*s == ' ')
				++space_count;
			else if (*s == '-' || !ft_isdigit(*s))
				return (LINE_TYPE_INVALID);
		}
		return ((space_count == 2) ? LINE_TYPE_ROOM : LINE_TYPE_INVALID);
	}
	while (*(++s))
	{
		if (*s == ' ' || *s == '-')
			return (LINE_TYPE_INVALID);
	}
	return (LINE_TYPE_LINK);
}

/*
**	Checks the following:
**		whether the pointer to the line exists
**		whether the line is not empty
**		whether the line does not start with L
**
**		whether it is a comment or the first occurrence of ##start or ##end
**
**		whether the line has either exactly two spaces, no hyphens, everything
**			after the spaces being only digits
**		OR
**			the line has exactly one hyphen and no spaces
**
**		whether, if the line is identified as a room, there have been no links
**
**	On success and if the line is identified as a room, adds to the room counter
*/

int			check_line(char *line, t_input_data *input)
{
	enum e_line_type	line_type;

	if (!line || !line[0] || line[0] == 'L')
		return (LINE_INVALID);
	if (line[0] == '#')
		return (check_comment(line, input));
	line_type = get_line_type(line);
	if (line_type == LINE_TYPE_INVALID
			|| (line_type == LINE_TYPE_ROOM && input->has_links))
		return (LINE_INVALID);
	if (line_type == LINE_TYPE_LINK)
		input->has_links = 1;
	else
		++(input->n_rooms);
	return (LINE_OK);
}
