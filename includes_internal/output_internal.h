/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:42:00 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:42:00 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_INTERNAL_H
# define OUTPUT_INTERNAL_H

# include "output.h"

t_ant	*build_ants(t_solution *sol);
void	del_ants(t_ant **ants, uint32_t n_ants);

#endif
