/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:34:37 by dhill             #+#    #+#             */
/*   Updated: 2017/12/04 21:06:33 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	assign_pts(t_ini *var, t_coord **data)
{
	int				i;
	int				w;
	static int		h;
	int				tmp_x;
	int				tmp_y;

	w = -1;
	i = -1;
	h > var->height ? h = 0 : 0;
	data[h] = (t_coord *)ft_memalloc(sizeof(t_coord) * (var->width + 1));
	while (++w < var->width)
	{
		tmp_x = w;
		tmp_y = h;
		data[h][w].z = ft_atoi(var->curr[w]) / 4;
		data[h][w].x = ((tmp_x * cos(A_Z) - tmp_y * sin(A_Z)) * Z) + CENTER_W;
		data[h][w].y = ((tmp_x * sin(A_Z) * cos(A_X) + tmp_y * cos(A_Z) *
					cos(A_X) - data[h][w].z * sin(A_X)) * Z) + CENTER_H;
	}
	while (var->curr[++i] != '\0')
		free(var->curr[i]);
	h++;
}

t_coord	**parse(char *str, t_ini *var)
{
	int			chk;
	int			i;
	char		*line;
	t_coord		**data;

	i = 0;
	line = NULL;
	(var->fd = open(str, O_RDONLY)) < 0 ? error("Error: Open failed.") : 0;
	data = (t_coord **)ft_memalloc(sizeof(t_coord *) * var->height);
	while ((chk = get_next_line(var->fd, &line)) > 0)
	{
		var->curr = ft_strsplit(line, ' ');
		!var->curr ? error("Error: Data parsing failed.") : 0;
		assign_pts(var, data);
		ft_strdel(&line);
	}
	chk == -1 ? error("Error: GNL failed.") : 0;
	close(var->fd);
	return (data);
}
