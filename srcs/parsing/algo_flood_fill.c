/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_flood_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:19:54 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/06 10:07:37 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	recursive(char **dup_map, int pos_x, int pos_y, bool *valid)
{
		flood_fill(dup_map, pos_x + 1, pos_y, valid);
		flood_fill(dup_map, pos_x - 1, pos_y, valid);
	if (dup_map[pos_y + 1])
		flood_fill(dup_map, pos_x, pos_y + 1, valid);
	else
	{
		*valid = false;
		return ;
	}
	if (pos_y && dup_map[pos_y - 1])
		flood_fill(dup_map, pos_x, pos_y - 1, valid);
	else
	{
		*valid = false;
		return ;
	}
}

void	flood_fill(char **dup_map, int pos_x, int pos_y, bool *valid)
{
	char	old_char;
	char	new_char;

	old_char = '0';
	new_char = 'x';
	if (dup_map[pos_y][pos_x] == '1' || dup_map[pos_y][pos_x] == new_char)
		return ;
	else if (dup_map[pos_y][pos_x] == old_char)
		dup_map[pos_y][pos_x] = new_char;
	else if (dup_map[pos_y][pos_x] == 'N'
		|| dup_map[pos_y][pos_x] == 'S'
		|| dup_map[pos_y][pos_x] == 'E'
		|| dup_map[pos_y][pos_x] == 'W')
		dup_map[pos_y][pos_x] = new_char;
	else
	{
		*valid = false;
		return ;
	}
	recursive(dup_map, pos_x, pos_y, valid);
}

int	algo_flood_fill(t_map *data_map)
{
	char	**dup_map;
	int		pos_x;
	int		pos_y;
	bool	valid;	

	valid = true;
	dup_map = data_map->dup_map;
	pos_x = data_map->pos_x;
	pos_y = data_map->pos_y;
	flood_fill(dup_map, pos_x, pos_y, &valid);
	if (valid == false)
	{
		exit_parsing(data_map, "Error\nCub3D: map not close");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
