/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:52:53 by dhill             #+#    #+#             */
/*   Updated: 2017/11/18 19:46:27 by dhill            ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_ini	*var;
	int		fd;

	if (ac != 2)
		error("Error: No map selected.");

	var = (t_ini *)malloc(sizeof(t_ini));
	if (!var)
		error("Error: Malloc failed.");
	var->id = mlx_init();
	var->win = mlx_new_window(var->id, 1000, 1000, av[1]);
	fd = open(av[1], O_RDONLY);
	validate(av[1], var);
	parse(av[1], var);
	printf("finished waiting for exit command.\n");
	mlx_key_hook(var->win, m_exit, NULL);
	mlx_hook(var->win, 17, 0, close_window, var);
	mlx_loop(var->id);
	return (0);
}
