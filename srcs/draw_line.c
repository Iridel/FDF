/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:40:53 by dhill             #+#    #+#             */
/*   Updated: 2017/12/04 21:08:04 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw(t_ini *var, t_coord **data)
{
	int	h;
	int w;

	h = 0;
	while (h < var->height)
	{
		w = 0;
		while (w < var->width)
		{
			if (w + 1 < var->width)
				draw_line(&data[h][w], &data[h][w + 1], var);
			if (h + 1 < var->height)
				draw_line(&data[h][w], &data[h + 1][w], var);
			w++;
		}
		h++;
	}
}

void	initalize_vb(t_draw *vb, t_coord *a, t_coord *b)
{
	int tmp;

	tmp = 0;
	vb->i = 0;
	vb->x = a->x;
	vb->y = a->y;
	vb->dx = abs(b->x - a->x);
	vb->dy = abs(b->y - a->y);
	vb->sx = ft_ispositive(b->x - a->x);
	vb->sy = ft_ispositive(b->y - a->y);
	vb->swap = 0;
	vb->z = MAX(a->z, b->z);
	vb->res = 2 * vb->dy - vb->dx;
	if (vb->dy > vb->dx)
	{
		tmp = vb->dx;
		vb->dx = vb->dy;
		vb->dy = tmp;
		vb->swap = 1;
	}
}

void	draw_line(t_coord *a, t_coord *b, t_ini *var)
{
	t_draw	vb;

	initalize_vb(&vb, a, b);
	while (vb.i <= vb.dx)
	{
		mlx_pixel_put(var->id, var->win, vb.x, vb.y,
					vb.z == 0 ? ORANGE : BLUE);
		while (vb.res > 0)
		{
			if (vb.swap)
				vb.x += vb.sx;
			else
				vb.y += vb.sy;
			vb.res -= 2 * vb.dx;
		}
		if (vb.swap)
			vb.y += vb.sy;
		else
			vb.x += vb.sx;
		vb.res += 2 * vb.dy;
		vb.i++;
	}
}
