/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:59:04 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/03 19:57:43 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check(int *player, int *i, int j, t_map *data_map)
{
	if (data_map->dup_map[j][*i] == 'N'
		|| data_map->dup_map[j][*i] == 'S'
		|| data_map->dup_map[j][*i] == 'E'
		|| data_map->dup_map[j][*i] == 'W')
	{
		data_map->player = data_map->dup_map[j][*i];
		data_map->pos_x = *i;
		data_map->pos_y = j;
		*player += 1;
		*i += 1;
	}
	else if (data_map->dup_map[j][*i] == '1'
		|| data_map->dup_map[j][*i] == '0'
		|| data_map->dup_map[j][*i] == 32)
	{
		*i += 1;
	}
	else
	{
		exit_parsing(data_map, "Error\nCub3D: invalid map");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_valid_char(t_map *data_map)
{
	int		i;
	int		j;
	int		player;

	i = 0;
	j = 0;
	player = 0;
	while (data_map->dup_map[j])
	{
		while (data_map->dup_map[j][i])
			check(&player, &i, j, data_map);
		i = 0;
		j++;
	}
	if (player != 1 || data_map->pos_x == 0 || data_map->pos_y == 0)
		exit_parsing(data_map, "Error\nCub3D: invalid player");
	if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'N')
		data_map->p_dir = N;
	else if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'S')
		data_map->p_dir = S;
	else if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'E')
		data_map->p_dir = E;
	else if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'W')
		data_map->p_dir = W;
	return (EXIT_SUCCESS);
}

static void	flood_fill(char **dup_map, int pos_x, int pos_y, bool *valid)
{
	char	old_char;
	char	new_char;

	old_char = '0';
	new_char = 'x';
	if (dup_map[pos_y][pos_x] == '1'
		|| dup_map[pos_y][pos_x] == new_char)
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
	flood_fill(dup_map, pos_x + 1, pos_y, valid);
	flood_fill(dup_map, pos_x - 1, pos_y, valid);
	flood_fill(dup_map, pos_x, pos_y + 1, valid);
	flood_fill(dup_map, pos_x, pos_y - 1, valid);
}

static int	algo_flood_fill(t_map *data_map)
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

int	check_map(t_map *data_map)
{
	check_valid_char(data_map);
	algo_flood_fill(data_map);
	printf("[player : %c] [enum : %d]\n", data_map->player, data_map->p_dir);
	return (EXIT_SUCCESS);
}
