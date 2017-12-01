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
# define W_SIZE		1000
# define CENTER		500
# define MAX_Z		(W_SIZE/var->width)

typedef struct	s_coord
{
	int			x;
	int			y;
	int			z;
} 				t_coord;

typedef struct	s_initalize
{
	void		*id;
	void		*win;
	void		*img;
	int			fd;
	int			width;
	int			height;
	int			zoom;
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
	
}				t_draw;

int					main(int ac, char **av);
void				error(char *str);

void				validate(char *av, t_ini *var);
void				check(char *str);
int					checkw(char **data);

t_coord				**parse(char *str, t_ini *var);
void				printstruct(t_coord **data, t_ini *var, char *str);
void				draw(t_ini *var, t_coord **data);
void				draw_line(t_coord *a, t_coord *b, t_ini *var);

//int					zoom_out(int key, int x, int y, t_ini *var);
#endif
