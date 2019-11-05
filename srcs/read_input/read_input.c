/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:09:55 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:10:03 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input_internal.h"
#include "solution.h"
#include "error.h"

static void	print_input(t_list *lines)
{
	ft_putlst(lines);
	ft_putchar('\n');
}

static int	clean_input(t_input_data *input)
{
	ft_lstdel(&input->lines, ft_delcontent);
	return (-1);
}

/*
**	Reads and validates the input.
**	Returns 0 on success and -1 on error (in which case it frees everything).
*/

int			read_input(t_graph **g, t_solution *sol, t_args *args)
{
	t_input_data	input;

	if (!g || !sol)
		return (-1);
	ft_memset(&input, 0, sizeof(t_input_data));
	if (read_lines(&input, &sol->n_ants) == -1)
		return (clean_input(&input));
	if (!(*g = ft_graphnew(get_next_prime(input.n_rooms))))
	{
		errno = EMEMORY;
		ft_lstdel(&input.lines, ft_delcontent);
		return (-1);
	}
	if (build_graph(*g, &input, &sol->start, &sol->end) == -1)
	{
		ft_graphdel(g);
		ft_lstdel(&input.lines, ft_delcontent);
		return (-1);
	}
	if (!args->silent)
		print_input(input.lines);
	ft_lstdel(&input.lines, ft_delcontent);
	return (0);
}
