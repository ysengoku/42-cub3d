/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:25:49 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/21 17:37:27 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_valid_to_true(t_cub3d *data)
{
	data->map.check.invalid_map = true;
	return ;
}

static void	recursive(t_cub3d *data, char **dup_map, int pos_x, int pos_y)
{
	if (pos_x + 1 < (int)ft_strlen(dup_map[pos_y]) && dup_map[pos_y][pos_x + 1])
		flood_fill_rec(data, dup_map, pos_x + 1, pos_y);
	else
		set_valid_to_true(data);
	if (pos_x - 1 >= 0 && dup_map[pos_y][pos_x - 1])
		flood_fill_rec(data, dup_map, pos_x - 1, pos_y);
	else
		set_valid_to_true(data);
	if (pos_y + 1 < data->map.map_len_y && dup_map[pos_y + 1]
		&& (int)ft_strlen(dup_map[pos_y + 1]) >= pos_x)
		flood_fill_rec(data, dup_map, pos_x, pos_y + 1);
	else
		set_valid_to_true(data);
	if (pos_y - 1 >= 0 && dup_map[pos_y - 1]
		&& (int)ft_strlen(dup_map[pos_y - 1]) >= pos_x)
		flood_fill_rec(data, dup_map, pos_x, pos_y - 1);
	else
		set_valid_to_true(data);
}

void	flood_fill_rec(t_cub3d *data, char **dup_map, int pos_x, int pos_y)
{
	data->map.check.limit_recursiv++;
	if (dup_map[pos_y][pos_x] != '1' && data->map.check.limit_recursiv > 100000)
	{
		dup_map[pos_y][pos_x] = 'P';
		return ;
	}
	else if (data->map.check.limit_recursiv > 100000)
		return ;
	if (dup_map[pos_y][pos_x] == '1')
		return ;
	else if (BONUS && dup_map[pos_y][pos_x] == 'D')
		dup_map[pos_y][pos_x] = '1';
	else if (BONUS && dup_map[pos_y][pos_x] == 'T')
	{
		dup_map[pos_y][pos_x] = '1';
		data->map.check.catch_treasure = true;
	}
	else if (dup_map[pos_y][pos_x] == '0')
		dup_map[pos_y][pos_x] = '1';
	else if (dup_map[pos_y][pos_x] == 'N'
		|| dup_map[pos_y][pos_x] == 'S'
		|| dup_map[pos_y][pos_x] == 'E'
		|| dup_map[pos_y][pos_x] == 'W')
		dup_map[pos_y][pos_x] = '1';
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
	recursive(data, dup_map, pos_x, pos_y);
}
