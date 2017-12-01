/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:25:23 by dhill             #+#    #+#             */
/*   Updated: 2017/11/25 23:51:25 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		checkw(char **curr)
{
	int	width;

	width = 0;
	while (curr[width] != '\0')
		width++;
	return (width);
}

void	check(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isalpha(s[i]) == 1)
			error("Error: Invalid file - alphabet found.");
		if ((s[i] == '-' && ft_isdigit(s[i + 1]) != 1) || s[i] == '\t')
			error("Error: Invalid file - tab or invalid '-' sign.");
		i++;
	}
}

void	validation(t_ini *var, t_values *val)
{
	while ((val->res = get_next_line(var->fd, &val->line)) > 0)
	{
		check(val->line);
		if ((var->curr = ft_strsplit(val->line, ' ')) == NULL)
			error("Error: Invalid file - No meaningful data.");
		if (!var->width)
		{
			var->width = checkw(var->curr);
			!var->width ? error("Error: First width check failed.") : 0;
		}
		else
		{
			val->w2 = checkw(var->curr);
			val->w2 != var->width ? error("Error: Invalid file - uneven") : 0;
		}
		while (var->curr[val->i2])
		{
			free(var->curr[val->i2]);
			val->i2++;
		}
		free(val->line);
		val->i++;
	}
	var->height = val->i;
	val->res == -1 ? error("GNL Error.") : 0;
}

void	validate(char *av, t_ini *var)
{
	t_values	*val;

	if (ft_strstr(av, ".fdf") == 0)
		error("Error: File extention is not .fdf.");
	if ((var->fd = open(av, O_RDONLY)) < 0)
		error("Error: Opening Failed.");
	var->width = 0;
	val = (t_values *)malloc(sizeof(t_values));
	val->i = 0;
	val->i2 = 0;
	val->w2 = 0;
	validation(var, val);
	close(var->fd);
	var->fd = 0;
}
