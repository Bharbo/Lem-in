/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:51:52 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/09/21 14:51:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu.h"

static long		next_space_or_end(char *s)
{
	long	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != ' ' && s[i] != '\0')
		++i;
	return (i);
}

static t_ant	*get_next_ant(char **line, t_viz_data *vdata)
{
	t_ant		*ant;
	uint32_t	sink;
	long		len;

	if (!line || !(*line) || !(**line) || **line != 'L'
		|| !(ant = ft_memalloc(sizeof(t_ant))))
		return (NULL);
	ant->iter = 0;
	ant->id = ft_atoi(*line + 1);
	*line = ft_strchr(*line + 1, '-') + 1;
	if ((len = next_space_or_end(*line)) == -1)
	{
		free(ant);
		return (NULL);
	}
	sink = ft_htgetid(vdata->graph, *line, len);
	ant->len_path = build_line(&ant->path,
			vdata->graph->items[vdata->ants[ant->id]]->value,
			vdata->graph->items[sink]->value);
	vdata->ants[ant->id] = sink;
	*line += len + ((*line)[len] != '\0');
	return (ant);
}

static t_list	*get_current_ants(t_viz_data *vdata)
{
	t_list	*current_ants;
	t_list	*newlst;
	t_ant	*ant;
	char	*line;

	current_ants = NULL;
	line = vdata->current_line->content;
	while ((ant = get_next_ant(&line, vdata)))
	{
		if (!ant->len_path || !(newlst = ft_lstnewlink(ant, sizeof(t_ant))))
		{
			del_ant(ant);
			ft_lstdel(&current_ants, del_ant_content);
			return (NULL);
		}
		ft_lstadd(&current_ants, newlst);
	}
	return (current_ants);
}

int				get_next_move(t_viz_data *vdata)
{
	t_list		*current_ants;
	uint16_t	i;

	if (!vdata->current_line || !vdata->current_line->content)
		return (0);
	if (line_type(vdata->current_line) != LT_TURN
		|| !(current_ants = get_current_ants(vdata)))
		return (-1);
	i = 0;
	while (i < LEN_TURN)
	{
		output_step(vdata, current_ants);
		++i;
	}
	ft_lstdel(&current_ants, del_ant_content);
	vdata->current_line = vdata->current_line->next;
	return (1);
}
