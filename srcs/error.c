/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:04:50 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/11 19:10:40 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	error(void)
{
	char	msg[MAX_ERROR_MSG_LEN];

	ft_putstr_fd("lem-in: ", 2);
	if (errno >= E_STARTINGCODE && errno < E_ENDINGCODE)
		ft_strcpy(msg, (char *[])ERROR_MSGS[errno - E_STARTINGCODE]);
	else
		ft_strcpy(msg, "Unknown error");
	ft_putendl_fd(msg, 2);
	return (1);
}
