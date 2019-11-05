/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static int	ft_error(t_viz_data *vdata, char *message)
{
	ft_putendl_fd(message, 2);
	return (clear_vdata(vdata, 1));
}

int			main(void)
{
	t_viz_data	vdata;

	ft_bzero(&vdata, sizeof(vdata));
	if (read_input(&vdata) == -1)
		return (ft_error(&vdata, "Error parsing input"));
	if (scale_coordinates(&vdata) == -1)
		return (ft_error(&vdata, "Some rooms are too close to each other"));
	setlocale(LC_ALL, "");
	initscr();
	while (get_next_move(&vdata) > 0)
		continue ;
	sleep(3);
	endwin();
	return (clear_vdata(&vdata, 0));
}
