/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:25:44 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 15:26:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mapdata(t_map *map)
{
	int	i;
	
	i = 0;
	while (i < map->map_len_y)
	{
		free(map->map[i]);
		map->map[i] = 0;
		free(map->data_map[i]);
		map->data_map[i] = 0;
		free(map->dup_map[i]);
		map->dup_map[i] = 0;
		i++;
	}
	free(map->map);
	free(map->data_map);
	free(map->dup_map);
	map->map = 0;
	map->data_map = 0;
	map->dup_map = 0;
	free(map->sprite_no);
	free(map->sprite_so);
	free(map->sprite_we);
	free(map->sprite_ea);
	map->sprite_no = 0;
	map->sprite_so = 0;
	map->sprite_we = 0;
	map->sprite_ea = 0;
}
