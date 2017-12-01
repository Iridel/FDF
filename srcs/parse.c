/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:34:37 by dhill             #+#    #+#             */
/*   Updated: 2017/11/29 15:59:11 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	assign_pts(t_ini *var, t_coord **data)
{
	int 			w;
	static int		h;
	int				i;
	   
	i = 0;
	w = 0;
	h > var->height ? h = 0: 0;
	data[h] = (t_coord *)ft_memalloc(sizeof(t_coord) * var->width);
	while (w < var->width)
	{
		data[h][w].z = ft_atoi(var->curr[w]) * var->zoom;
		data[h][w].x = (w * var->zoom) + (CENTER - ((var->width * var->zoom)/2));
		data[h][w].y = (h * var->zoom) + (CENTER - ((var->height * var->zoom)/2));
		w++;
	}
	while (var->curr[i] != '\0')
	{
		free(var->curr[i]);
		i++;
	}
	h++;
}

void	printstruct(t_coord **data, t_ini *var, char *str)
{
	int w = 0;
	int h = 0;

	ft_putendl(str);
	while (h < var->height)
	{
		printf("----------row: %d----------\n", h);
		while (w < var->width)
		{
			printf("-col: %d-\n", w);
			printf("X: %d, Y: %d, Z: %d\n", data[h][w].x, data[h][w].y, data[h][w].z);
			w++;
		}
		w = 0;
		h++;
	}
}

t_coord	**parse(char *str, t_ini *var)
{
	int			chk;
	int 		i;
	char		*line;
	t_coord		**data;

	i = 0;
	line = NULL;
	//printf("Height: %d, Width: %d\n", var->height, var->width);
	(var->fd = open(str, O_RDONLY)) < 0 ? error("Error: Parse open failed.") : 0;
	data = (t_coord **)ft_memalloc(sizeof(t_coord *) * var->height);
	while ((chk = get_next_line(var->fd, &line)) > 0)
	{
		var->curr = ft_strsplit(line, ' ');
		!var->curr ? error("Error: Data parsing failed.") : 0;
		assign_pts(var, data);	
		ft_strdel(&line);
	}
	chk == -1 ? error("Error: GNL failed.") : 0;
	return (data);
}
