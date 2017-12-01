/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:40:53 by dhill             #+#    #+#             */
/*   Updated: 2017/11/27 23:52:19 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw(t_ini *var, t_coord **data)
{
	int	h;
	int w;

	h = 0;
	w = 0;

	while (h < var->height)
	{
		while (w < var->width)
		{
			if (w < var->width - 1)
				draw_line(&data[h][w], &data[h][w + 1], var);
			if (h < var->height - 1)
				draw_line(&data[h][w], &data[h + 1][w], var);
			w++;
		}
		w = 0;
		h++;
	}
}

void	initalize_vb(t_draw *vb, t_coord *a, t_coord *b)
{
	vb->i = 0;
	vb->x = a->x;
	vb->y = a->y;
	vb->dx = abs(b->x - a->x);
	vb->dy = abs(b->y - a->y);
	vb->sx = ft_ispositive(b->x - a->x);
	vb->sy = ft_ispositive(b->y - a->y);
	vb->swap = 0;
}

void	draw_line(t_coord *a, t_coord *b, t_ini *var)
{
	t_draw	vb;
	int		tmp;
	int		res;

	initalize_vb(&vb, a, b);
	if (vb.dy > vb.dx)
	{
		tmp = vb.dx;
		vb.dx = vb.dy;
		vb.dy = tmp;
		vb.swap = 1;
	}
	res = 2 * vb.dy - vb.dx;
	while (vb.i < vb.dx)
	{
		mlx_pixel_put(var->id, var->win, vb.x, vb.y, PRPL_R);
		while (res >= 0)
		{
			res -= 2 * vb.dx;
			if (vb.swap)
				vb.x += vb.sx;
			else
				vb.y += vb.sy;
		}
		res += 2 * vb.dy;
		if (vb.swap)
			vb.y += vb.sy;
		else
			vb.x += vb.sx;
		vb.i++;
	}
	mlx_pixel_put(var->id, var->win, vb.x, vb.y, PRPL_R);
}
