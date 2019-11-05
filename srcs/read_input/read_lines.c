/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:10:15 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:12:23 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"
#include "error.h"

static int	add_line(t_input_data *input, char *line)
{
	static t_list	*current;
	t_list			*newlst;

	if (!(newlst = ft_lstnewlink(line, 0)))
		return (-1);
	if (!input->lines)
		input->lines = newlst;
	else
		ft_lstappend(current, newlst);
	current = newlst;
	return (0);
}

static int	check_errors(t_input_data *input)
{
	if (!input->n_rooms)
	{
		errno = ENOROOMS;
		return (-1);
	}
	if (!input->has_links)
	{
		errno = ENOLINKS;
		return (-1);
	}
	if (!input->has_start)
	{
		errno = ENOSTART;
		return (-1);
	}
	if (!input->has_end)
	{
		errno = ENOEND;
		return (-1);
	}
	return (0);
}

static int	delete_lines(char *line, t_list **lines, enum e_line_status status)
{
	free(line);
	ft_lstdel(lines, ft_delcontent);
	errno = ((status == LINE_INVALID) ? EINVALIDINPUT : EMEMORY);
	return (-1);
}

static int	write_ants(t_input_data *input, uint32_t *ants)
{
	long	n_ants;
	char	*line;

	line = NULL;
	while (ft_gnl(0, &line) > 0)
	{
		if (add_line(input, line) == -1)
			return (delete_lines(line, &input->lines, LINE_COMMENT));
		if (line[0] != '#')
			break ;
	}
	if (!line || !is_valid_number(line))
	{
		errno = line ? EINVALIDANTS : ENOINPUT;
		return (-1);
	}
	n_ants = ft_ltoi(line);
	if (n_ants <= 0 || (int)n_ants != n_ants)
	{
		errno = EINVALIDNUMBERANTS;
		return (-1);
	}
	*ants = (int)n_ants;
	return (0);
}

int			read_lines(t_input_data *input, uint32_t *ants)
{
	char				*line;
	enum e_line_status	status;

	if (write_ants(input, ants) == -1)
		return (-1);
	while (ft_gnl(0, &line) > 0)
	{
		status = check_line(line, input);
		if (status == LINE_INVALID
				|| add_line(input, line) == -1)
			return (delete_lines(line, &input->lines, status));
	}
	return (check_errors(input));
}
