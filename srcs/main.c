/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:52:53 by dhill             #+#    #+#             */
/*   Updated: 2017/11/30 17:59:22 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		close_window(t_ini *var)
{
	mlx_destroy_window(var->id, var->win);
	exit(0);
	return (0);
}

int		m_exit(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void	error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void	initalize(t_ini *var, char *str)
{
	!var ? error("Error: Malloc for t_ini var failed.") : 0;
	var->id = mlx_init();
	var->win = mlx_new_window(var->id, W_SIZE, W_SIZE, str);
	var->fd = open(str, O_RDONLY);
	var->zoom = 10;
}

int		main(int ac, char **av)
{
	t_ini	*var;

	if (ac != 2)
		error("Error: No map selected.");
	var = (t_ini *)malloc(sizeof(t_ini));
	var->name = av[1];
	initalize(var, var->name);
	validate(var->name, var);
	var->data = parse(var->name, var);
	draw(var, var->data);
	printf("finished waiting for exit command.\n");
	mlx_key_hook(var->win, m_exit, NULL); //for the esc button
	mlx_hook(var->win, 17, 0, close_window, var); //clicking the red 'x'
//	mlx_hook(var->win, 4, 0, zoom_out, var); //zoom
	mlx_loop(var->id);
	return (0);
}
