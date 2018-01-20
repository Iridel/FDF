/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 20:30:56 by dhill             #+#    #+#             */
/*   Updated: 2017/12/04 20:52:18 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define ORANGE		0x00f87014
# define BLUE		0x003299ff
# define WINE_R		0x00D40439
# define PRPL_R		0x00A30051
# define W_SIZE		1000
# define MAX(a, b)	((a) > (b) ? (a) : (b))
# define PI			3.14159265
# define A_X		(PI / 180) * 45
# define A_Z		(PI / 180) * 45
# define Z			10
# define CENTER_W	(W_SIZE/2) - (var->width * Z/2)
# define CENTER_H	(W_SIZE/2) - (var->height * Z/2)

typedef struct	s_coord
{
	int			x;
	int			y;
	int			z;
}				t_coord;

typedef struct	s_initalize
{
	void		*id;
	void		*win;
	void		*img;
	int			fd;
	int			width;
	int			height;
	char		*name;
	t_coord		**data;
	char		**curr;
}				t_ini;

typedef struct	s_val_var
{
	int			res;
	int			w2;
	int			i;
	int			i2;
	char		*line;
}				t_values;

typedef struct	s_draw_var
{
	int			i;
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			swap;
	int			z;
	int			res;
}				t_draw;

int				main(int ac, char **av);
void			error(char *str);

void			validate(char *av, t_ini *var);
void			check(char *str);
int				checkw(char **data);

t_coord			**parse(char *str, t_ini *var);
void			draw(t_ini *var, t_coord **data);
void			draw_line(t_coord *a, t_coord *b, t_ini *var);
#endif
