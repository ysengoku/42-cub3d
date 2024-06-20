/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:22:44 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/20 07:50:56 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_is_map(char *line)
{
	int	i;

	i = 0;
	if (!BONUS)
	{
		while (line[i] == ' ' || line[i] == '1' || line[i] == '0'
			|| line[i] == 'S' || line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'W')
			i++;
	}
	else
	{
		while (line[i] == ' ' || line[i] == '1' || line[i] == '0'
			|| line[i] == 'S' || line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'W' || line[i] == 'D' || line[i] == 'T')
			i++;
	}
	if (line[i] == '\0')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_file(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (line_is_map(data->map.data_map[i]) == EXIT_SUCCESS)
			break ;
		if (line_is_map(data->map.data_map[i]) == EXIT_FAILURE)
			data->map.check.nbr_data++;
		i++;
	}
	if (data->map.check.nbr_data != 6)
	{
		free_texture_paths(data->wall, 4);
		exit_parsing(&data->map, "Error\nCub3D: bad data detected");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
