/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:21 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:05:55 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"
#include "find_solution.h"
#include "output.h"
#include "error.h"

/*
**	As there's only one possible option, keeping it simple for now.
*/

static int	parse_args(int argc, char **argv, t_args *args)
{
	ft_memset(args, 0, sizeof(t_args));
	if (argc <= 1)
		return (0);
	if (argc > 2 || ft_strcmp(argv[1], "-s"))
		return (-1);
	args->silent = 1;
	return (0);
}

int			main(int argc, char **argv)
{
	t_args		args;
	t_graph		*g;
	t_solution	sol;

	if (parse_args(argc, argv, &args) == -1)
		return (error());
	ft_memset(&sol, 0, sizeof(t_solution));
	if (read_input(&g, &sol, &args) == -1)
		return (error());
	find_solution(g, &sol);
	if (!sol.paths)
	{
		ft_graphdel(&g);
		errno = ENOPATH;
		return (error());
	}
	output(g, &sol);
	ft_graphdel(&g);
	del_paths(&sol.paths, sol.n_paths);
	return (0);
}
