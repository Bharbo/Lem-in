/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:40:29 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/09 19:40:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_INPUT_H
# define READ_INPUT_H

# include "libft.h"
# include "solution.h"
# include "args.h"

/*
**	The function reads and validates the input.
**	Returns 0 on success and -1 on error (in which case it frees everything).
*/

int read_input(t_graph **g, t_solution *sol, t_args *args);

#endif
