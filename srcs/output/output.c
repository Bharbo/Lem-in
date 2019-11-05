/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:35 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:50:34 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "output_internal.h"

static uint32_t	*build_ants_per_path(t_solution *sol)
{
	uint32_t	*out;
	uint32_t	i;
	uint32_t	ants_left;

	if (!sol || !sol->paths || !sol->n_paths
			|| !(out = (uint32_t *)ft_memalloc(sizeof(uint32_t)
					* sol->n_paths)))
		return (NULL);
	i = 0;
	ants_left = sol->n_ants;
	while (i < sol->n_paths)
	{
		out[i] = sol->turns - (sol->paths[i][0] - 1) + 1;
		if (ants_left < out[i])
			out[i] = ants_left;
		ants_left -= out[i];
		++i;
	}
	return (out);
}

static uint32_t	update_ants_passed(uint32_t *ants_passed, t_solution *sol)
{
	uint32_t	i;

	i = *ants_passed;
	while (i < sol->n_ants && sol->ants[i].node != NULL)
	{
		if (*sol->ants[i].node != sol->end)
			break ;
		++i;
	}
	*ants_passed = i;
	return (i);
}

static uint32_t	move_ants(uint32_t i, t_graph *g, t_solution *sol)
{
	while (i < sol->n_ants && sol->ants[i].node != NULL)
	{
		if (*sol->ants[i].node != sol->end)
		{
			++(sol->ants[i].node);
			ft_putstr(sol->ants[i].name);
			write(1, g->items[*sol->ants[i].node]->key,
					g->items[*sol->ants[i].node]->ksize);
			write(1, " ", 1);
		}
		++i;
	}
	return (i);
}

static void		start_new_paths(uint32_t i, t_graph *g, t_solution *sol)
{
	uint32_t	j;

	j = 0;
	while (j < sol->n_paths && i + j < sol->n_ants)
	{
		if (!sol->ants_per_path[j])
			break ;
		sol->ants[i + j].node = sol->paths[j] + 2;
		ft_putstr(sol->ants[i + j].name);
		write(1, g->items[*sol->ants[i + j].node]->key,
				g->items[*sol->ants[i + j].node]->ksize);
		write(1, " ", 1);
		--(sol->ants_per_path[j]);
		++j;
	}
	write(1, "\n", 1);
}

void			output(t_graph *g, t_solution *sol)
{
	uint32_t	ants_passed;
	uint32_t	i;

	if (!g || !sol || !(sol->ants = build_ants(sol)))
		return ;
	if (!(sol->ants_per_path = build_ants_per_path(sol)))
	{
		del_ants(&sol->ants, sol->n_ants);
		return ;
	}
	ants_passed = 0;
	while (1)
	{
		i = update_ants_passed(&ants_passed, sol);
		i = move_ants(i, g, sol);
		if (ants_passed < sol->n_ants)
			start_new_paths(i, g, sol);
		else
			break ;
	}
	del_ants(&sol->ants, sol->n_ants);
	free(sol->ants_per_path);
	sol->ants_per_path = NULL;
}
