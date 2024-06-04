/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:51 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/04 14:57:41 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_x * MOVE);
	dest_y = player->pos_y + (player->dir_y * MOVE);
	if (map->map[dest_x][(int)floor(player->pos_y)] != '1')
		player->pos_x += player->dir_x * MOVE;
	if (map->map[(int)floor(player->pos_x)][dest_y] != '1')
		player->pos_y += player->dir_y * MOVE;
	printf("dest_x %d, dest_y %d\n", dest_x, dest_y);
	// if (map->map[dest_x][(int)floor(player->pos_y)] != '1'
	// 	&& map->map[(int)floor(player->pos_x)][dest_y] != '1'
	// 	&& map->map[dest_x][dest_y] != '1')
	// if (map->map[dest_x][dest_y] != '1')
	{
		player->pos_x += player->dir_x * MOVE;
		player->pos_y += player->dir_y * MOVE;
		printf("player->pos_x %f, player->pos_y %f\n", player->pos_x, player->pos_y);
	}
	data->player.moved = 1;
}

void	move_backward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_x * -1 * MOVE);
	dest_y = player->pos_y + (player->dir_y * -1 * MOVE);
	if (map->map[dest_x][(int)player->pos_y] != '1')
		player->pos_x += player->dir_x * -1 * MOVE;
	if (map->map[(int)player->pos_x][dest_y] != '1')
		player->pos_y += player->dir_y * -1 * MOVE;
	data->player.moved = 1;
}

void	move_left(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_y * MOVE);
	dest_y = player->pos_y + (player->dir_x * -1 * MOVE);
	if (map->map[dest_x][(int)player->pos_y] != '1')
		player->pos_x += player->dir_y * MOVE;
	if (map->map[(int)player->pos_x][dest_y] != '1')
		player->pos_y += player->dir_x * -1 * MOVE;
	data->player.moved = 1;
}

void	move_right(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_y * -1 * MOVE);
	dest_y = player->pos_y + (player->dir_x * MOVE);
	if (map->map[dest_x][(int)player->pos_y] != '1')
		player->pos_x += player->dir_y * -1 * MOVE;
	if (map->map[(int)player->pos_x][dest_y] != '1')
		player->pos_y += player->dir_x * MOVE;
	data->player.moved = 1;
}
