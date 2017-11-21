#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define YELLOW		0x00f2dc00
# define ORANGE		0x00ec7700
# define WINE_R		0x00D40439
# define PRPL_R		0x00A30051

typedef struct	s_coord
{
	int			x;
	int			y;
	int			z;
	int			*color;
} 				t_coord;

typedef struct	s_initalize
{
	void		*id;
	void		*win;
	int			fd;
	int			width;
	int			height;
	int			fl;
	char		**curr;
}				t_ini;

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
	
}				t_draw;

int					main(int ac, char **av);
void				error(char *str);

void				validate(char *av, t_ini *var);
void				validation(t_ini *var);
void				check(char *str);
int					checkw(char **data);

void				parse(char *str, t_ini *var);
void				printstruct(t_coord *data, t_ini *var, char *str);
void				draw_horizontal(t_ini *var, t_coord *c_data);
void				draw_vertical(t_ini *var, t_coord *p_data, t_coord *c_data);
void				draw_line(t_coord *a, t_coord *b, t_ini *view);
#endif
