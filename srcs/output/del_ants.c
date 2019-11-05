/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:35 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:35 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output_internal.h"

void	del_ants(t_ant **ants, uint32_t n_ants)
{
	uint32_t	i;

	if (!ants || !(*ants))
		return ;
	i = 0;
	while (i < n_ants)
	{
		free((*ants)[i].name);
		++i;
	}
	free(*ants);
	*ants = NULL;
}
