/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

int		clear_vdata(t_viz_data *vdata, int return_code)
{
	if (vdata->img)
		free(vdata->img);
	if (vdata->lines)
		ft_lstdel(&vdata->lines, ft_delcontent);
	if (vdata->graph)
		ft_htdel(&vdata->graph, ft_hidel);
	if (vdata->links)
		ft_lstdel(&vdata->links, ft_delcontent);
	if (vdata->ants)
		free(vdata->ants);
	return (return_code);
}

void	del_ant(t_ant *ant)
{
	if (ant->len_path)
		free(ant->path);
	free(ant);
}

void	del_ant_content(void **content, size_t *size)
{
	del_ant(*content);
	*content = NULL;
	if (size)
		*size = 0;
}
