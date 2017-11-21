/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:34:37 by dhill             #+#    #+#             */
/*   Updated: 2017/11/18 18:39:58 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//can make this return a t_coord grid or smth
//Idea is to re-open the fd and actually parse/store the map
//since now we know everything is kosher. After that start the drawing
//phase with draw_line to the grid points. Draw_line.c can store any
//helper functions for generate.c which will generate the design, then one
//last file that will be used for rotations. As for mouse hooks, maybe have
//mouse click and drag entire drawing around?


t_coord	*assign_pts_curr(t_ini *var)
{
	t_coord			*data;
	int 			w;
	static int		h;
	int i = 0;

	w = 0;
	h > var->height ? h = 0: 0;
	data = (t_coord *)malloc(sizeof(t_coord) * var->width);
	while (w < var->width)
	{
		data[w].z = ft_atoi(var->curr[w]) * 10;
		data[w].x = w * 10;
		data[w].y = h * 10;
		w++;
	}
	while (var->curr[i] != '\0')
	{
		free(var->curr[i]);
		i++;
	}
	h++;
	return (data);
	//assign points from current here
	//to t_coords that will be put into horizontal.
}

void	printstruct(t_coord *data, t_ini *var, char *str)
{
	int i = 0;

	ft_putendl(str);
	while (i < var->width)
	{
		printf("X: %d, Y: %d, Z: %d\n", data[i].x, data[i].y, data[i].z);
		i++;
	}
}

void	parse(char *str, t_ini *var)
{
	int			chk;
	int 		i;
	char		*line;
	t_coord		*p_data;
	t_coord		*c_data;

	i = 0;
	line = NULL;
	var->fl = 0;
	printf("Height: %d, Width: %d\n", var->height, var->width);
	(var->fd = open(str, O_RDONLY)) < 0 ? error("Error: Parse open failed.") : 0;
	while ((chk = get_next_line(var->fd, &line)) > 0)
	{
		var->curr = ft_strsplit(line, ' ');
		!var->curr ? error("Error: Data parsing failed.") : 0;
		c_data = assign_pts_curr(var);
		draw_horizontal(var, c_data);
		if (var->fl == 0)
		{
			var->fl = 1;
			printf("first time\n");
			p_data = (t_coord *)malloc(sizeof(t_coord) * var->width);
			p_data = c_data;
		}
		else
		{
			printf("all other times\n");
			draw_vertical(var, p_data, c_data);
			free(p_data);
			p_data = c_data;
			
		}
		ft_strdel(&line);
	}
	chk == -1 ? error("Error: GNL failed.") : 0;
}
