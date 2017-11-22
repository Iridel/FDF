/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:40:53 by dhill             #+#    #+#             */
/*   Updated: 2017/11/20 17:45:56 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_vertical(t_ini *var, t_coord *p_data, t_coord *c_data)
{
	int	i;
	int n;

	i = 0;
	printf("Drawing vertical\n");
	while (i < var->width)
	{
		n = p_data[i].y;
		while (n < c_data[i].y && p_data[i].x == c_data[i].x)
		{
			mlx_pixel_put(var->id, var->win, p_data[i].x, n, PRPL_R);
			n++;	
		}
		i++;
	}
}

void	draw_horizontal(t_ini *var, t_coord *c_data)
{
	int i;

	i = 0;
	printf("Drawing horizontal\n");
	while (i < var->width)
	{
		draw_line(&c_data[i], &c_data[i + 1], var);
		i++;
	}
}

int		abs_val(int n)
{
	return (n < 0 ? -n : n);
}

void	initalize_var(t_draw *var, t_coord *a, t_coord *b)
{
	var->i = 0;
	var->x = a->x;
	var->y = a->y;
	var->dx = abs_val(b->x - a->x);
	var->dy = abs_val(b->y - a->y);
	var->sx = ft_ispositive(b->x - a->x);
	var->sy = ft_ispositive(b->y - a->y);
	var->swap = 0;
}

void	draw_line(t_coord *a, t_coord *b, t_ini *view)
{
	t_draw	var;
	int		tmp;
	int		res;

	printf("yes?\n");
	initalize_var(&var, a, b);
	if (var.dy > var.dx)
	{
		tmp = var.dx;
		var.dx = var.dy;
		var.dy = tmp;
		var.swap = 1;
		printf("yes?\n");
	}
	res = 2 * var.dy - var.dx;
	while (var.i < var.dx)
	{
		mlx_pixel_put(view->id, view->win, var.x, var.y, PRPL_R);
		while (res >= 0)
		{
			res -= 2 * var.dx;
			if (var.swap)
				var.x += var.sx;
			else
				var.y += var.sy;
		}
		res += 2 * var.dy;
		if (var.swap)
			var.y += var.sy;
		else
			var.x += var.sx;
		var.i++;
	}
}
