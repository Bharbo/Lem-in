/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:28 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:28 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_solution_internal.h"

void	del_paths(uint32_t ***paths, uint32_t n_paths)
{
	uint32_t	i;

	if (!paths || !(*paths))
		return ;
	i = 0;
	while (i < n_paths)
	{
		if ((*paths)[i])
			free((*paths)[i]);
		++i;
	}
	free(*paths);
	*paths = NULL;
}
