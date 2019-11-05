/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:04:03 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:04:04 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include "libft.h"

# define MAX_ERROR_MSG_LEN 64

/*
**	150 is chosen as the starting code to avoid collisions with existing codes
*/

# define E_STARTINGCODE 150

enum	e_custom_error_code
{
	ENOINPUT = E_STARTINGCODE,
	ENOROOMS,
	ENOLINKS,
	ENOSTART,
	ENOEND,
	EINVALIDINPUT,
	EINVALIDANTS,
	EINVALIDNUMBERANTS,
	EINVALIDROOM,
	EDUPLICATEROOM,
	EDUPLICATELINK,
	EMEMORY,
	ENOPATH,
	E_ENDINGCODE
};

# define E0 "No input found"
# define E1 "No rooms found"
# define E2 "No links found"
# define E3 "No start found"
# define E4 "No end found"
# define E5 "Invalid input"
# define E6 "Ants could not be parsed"
# define E7 "Ants number is invalid"
# define E8 "Room doesn't exist"
# define E9 "Duplicate room found"
# define E10 "Duplicate link found"
# define E11 "Memory allocation failed"
# define E12 "No path found"
# define E13 "Invalid option"
# define ERROR_MSGS {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13}

int		error(void);

#endif
