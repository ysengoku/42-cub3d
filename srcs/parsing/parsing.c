/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:54:57 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/01 17:12:49 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		printf("%s\n", map[j]);
		j++;
	}
}

static void	display_data(t_map *data_map)
{
	printf("\n[DATA MAP]\n\n");
	display_map(data_map->data_map);
	printf("\n[DUP MAP]\n\n");
	display_map(data_map->dup_map);
	printf("\n[MAP]\n\n");
	display_map(data_map->map);
	printf("\n\n");
	printf("[max len x] : %d\n", data_map->map_len_x);
	printf("[max len y] : %d\n", data_map->map_len_y);
	printf("[sprite_NO] : %s\n", data_map->sprite_NO);
	printf("[sprite_SO] : %s\n", data_map->sprite_SO);
	printf("[sprite_WE] : %s\n", data_map->sprite_WE);
	printf("[sprite_EA] : %s\n", data_map->sprite_EA);
	printf("[F_RGB]     : [R]%d, [G]%d, [B]%d\n", data_map->F_RGB[0], data_map->F_RGB[1], data_map->F_RGB[2]);
	printf("[C_RGB]     : [R]%d, [G]%d, [B]%d\n", data_map->C_RGB[0], data_map->C_RGB[1], data_map->C_RGB[2]);
}

int	parsing(char *file, t_map *data_map)
{
	if (!file)
		return (EXIT_FAILURE);
	ft_memset(data_map, 0, sizeof(t_map));
	data_map->data_map = get_file(file);
	if (!data_map->data_map)
		return (ft_perror_exit("Error\nCub3D", EXIT_FAILURE), EXIT_FAILURE);
	get_data(data_map);
	get_maps(data_map);
	check_map(data_map);
	display_data(data_map);
	return (EXIT_SUCCESS);
}
