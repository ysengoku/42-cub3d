/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_flood_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:19:54 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/21 17:23:03 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	choose_flood_fill(t_cub3d *data)
{
	flood_fill_rec(data, data->map.dup_map, data->map.pos_x, data->map.pos_y);
	flood_fill_iter(data, data->map.dup_map);
	if (data->map.check.invalid_map)
	{
		if (!BONUS)
			free_texture_paths(data->wall, 4);
		else
			free_texture_paths(data->wall, 12);
		exit_parsing(&data->map, "Error\nCub3D: map not close");
	}
	if (data->map.check.catch_treasure == false)
	{
		free_texture_paths(data->wall, 12);
		exit_parsing(&data->map, "Error\nCub3D: treasure not reached");
	}
	return (EXIT_SUCCESS);
}
