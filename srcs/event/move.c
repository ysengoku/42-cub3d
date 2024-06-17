/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:51 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 10:38:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	// dest_x = player->pos_x + (player->dir_x * MOVE);
	// dest_y = player->pos_y + (player->dir_y * MOVE);
	// if (map->map[(int)player->pos_y][dest_x] != '1'
	// 	&& map->map[(int)player->pos_y][dest_x] != 'D')
	// {
	// 	player->pos_x += player->dir_x * MOVE;
	// 	data->map.pos_x = player->pos_x;
	// }
	// if (map->map[dest_y][(int)player->pos_x] != '1'
	// 	&& map->map[dest_y][(int)player->pos_x] != 'D')
	// {
	// 	player->pos_y += player->dir_y * MOVE;
	// 	data->map.pos_y = player->pos_y;
	// }
	dest_x = player->pos.x + (player->dir.x * MOVE);
	dest_y = player->pos.y + (player->dir.y * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D')
	{
		player->pos.x += player->dir.x * MOVE;
		data->map.pos_x = player->pos.x;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D')
	{
		player->pos.y += player->dir.y * MOVE;
		data->map.pos_y = player->pos.y;
	}
}

void	move_backward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	// dest_x = player->pos_x + (player->dir_x * -1 * MOVE);
	// dest_y = player->pos_y + (player->dir_y * -1 * MOVE);
	// if (map->map[(int)player->pos_y][dest_x] != '1'
	// 	&& map->map[(int)player->pos_y][dest_x] != 'D')
	// {
	// 	player->pos_x += player->dir_x * -1 * MOVE;
	// 	data->map.pos_x = player->pos_x;
	// }
	// if (map->map[dest_y][(int)player->pos_x] != '1'
	// 	&& map->map[dest_y][(int)player->pos_x] != 'D')
	// {
	// 	player->pos_y += player->dir_y * -1 * MOVE;
	// 	data->map.pos_y = player->pos_y;
	// }
	dest_x = player->pos.x + (player->dir.x * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.y * -1 * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D')
	{
		player->pos.x += player->dir.x * -1 * MOVE;
		data->map.pos_x = player->pos.x;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D')
	{
		player->pos.y += player->dir.y * -1 * MOVE;
		data->map.pos_y = player->pos.y;
	}
}

void	move_left(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	// dest_x = player->pos_x + (player->dir_y * MOVE);
	// dest_y = player->pos_y + (player->dir_x * -1 * MOVE);
	// if (map->map[(int)player->pos_y][dest_x] != '1'
	// 	&& map->map[(int)player->pos_y][dest_x] != 'D')
	// {
	// 	player->pos_x += player->dir_y * MOVE;
	// 	data->map.pos_x = player->pos_x;
	// }
	// if (map->map[dest_y][(int)player->pos_x] != '1'
	// 	&& map->map[dest_y][(int)player->pos_x] != 'D')
	// {
	// 	player->pos_y += player->dir_x * -1 * MOVE;
	// 	data->map.pos_y = player->pos_y;
	// }
	dest_x = player->pos.x + (player->dir.y * MOVE);
	dest_y = player->pos.y + (player->dir.x * -1 * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D')
	{
		player->pos.x += player->dir.y * MOVE;
		data->map.pos_x = player->pos.x;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D')
	{
		player->pos.y += player->dir.x * -1 * MOVE;
		data->map.pos_y = player->pos.y;
	}
}

void	move_right(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	// dest_x = player->pos_x + (player->dir_y * -1 * MOVE);
	// dest_y = player->pos_y + (player->dir_x * MOVE);
	// if (map->map[(int)player->pos_y][dest_x] != '1'
	// 	&& map->map[(int)player->pos_y][dest_x] != 'D')
	// {
	// 	player->pos_x += player->dir_y * -1 * MOVE;
	// 	data->map.pos_y = player->pos_y;
	// }
	// if (map->map[dest_y][(int)player->pos_x] != '1'
	// 	&& map->map[dest_y][(int)player->pos_x] != 'D')
	// {
	// 	player->pos_y += player->dir_x * MOVE;
	// 	data->map.pos_y = player->pos_y;
	// }
	dest_x = player->pos.x + (player->dir.y * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.x * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D')
	{
		player->pos.x += player->dir.y * -1 * MOVE;
		data->map.pos_y = player->pos.y;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D')
	{
		player->pos.y += player->dir.x * MOVE;
		data->map.pos_y = player->pos.y;
	}
}
