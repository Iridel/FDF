/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:25:23 by dhill             #+#    #+#             */
/*   Updated: 2017/11/20 13:56:11 by dhill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		checkw(char **curr)
{
	int	depth;

	depth = 0;
	while (curr[depth] != '\0')
		depth++;
	return (depth);
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

void	validation(t_ini *var)
{
	int 	res;
	int 	w2;
	int 	i;
	char	*line;

	i = 0;
	w2 = 0;
	var->width = 0;
	while ((res = get_next_line(var->fd, &line)) > 0)
	{
		check(line);
		if ((var->curr = ft_strsplit(line, ' ')) == NULL)
			error("Error: Invalid file - No meaningful data.");
		if (!var->width)
		{
			var->width = checkw(var->curr);
			!var->width ? error("Error: First width check failed.") : 0;
		}
		else
		{
			w2 = checkw(var->curr);
			if (w2 != var->width)
				error("Error: Invalid file - Lines uneven.");
		}
		free(var->curr); //needs to free each string else wont free right
		free(line);
		i++;
	}
	var->height = i;
	res == -1 ? error("GNL Error.") : 0;
	res == 0 ? ft_putendl("File reading is finished.") : 0;
}

void	validate(char *av, t_ini *var)
{
	if (ft_strstr(av, ".fdf") == 0)
		error("Error: File extention is not .fdf.");
	if ((var->fd = open(av, O_RDONLY)) < 0)
		error("Error: Opening Failed.");
	validation(var);
	close(var->fd);
	var->fd = 0;
}
