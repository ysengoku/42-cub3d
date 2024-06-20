/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_flood_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:19:54 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/20 17:21:24 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill_rec(t_cub3d *data, char **dup_map, int pos_x, int pos_y);

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

static void	flood_fill_rec(t_cub3d *data, char **dup_map, int pos_x, int pos_y)
{
	data->map.check.old_char = '0';
	data->map.check.new_char = 'x';
	if (dup_map[pos_y][pos_x] == '1'
		|| dup_map[pos_y][pos_x] == data->map.check.new_char)
		return ;
	else if (BONUS && dup_map[pos_y][pos_x] == 'D')
		dup_map[pos_y][pos_x] = data->map.check.new_char;
	else if (BONUS && dup_map[pos_y][pos_x] == 'T')
	{
		dup_map[pos_y][pos_x] = data->map.check.new_char;
		data->map.check.catch_treasure = true;
	}
	else if (dup_map[pos_y][pos_x] == data->map.check.old_char)
		dup_map[pos_y][pos_x] = data->map.check.new_char;
	else if (dup_map[pos_y][pos_x] == 'N'
		|| dup_map[pos_y][pos_x] == 'S'
		|| dup_map[pos_y][pos_x] == 'E'
		|| dup_map[pos_y][pos_x] == 'W')
		dup_map[pos_y][pos_x] = data->map.check.new_char;
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
	recursive(data, dup_map, pos_x, pos_y);
}

static int	find_pos(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		while(map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
			{
				if (c == 'x')
				{
					return (i);
				}
				else if (c == 'y')
				{
					return (j);
				}
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

static int	apply_cross_player(t_cub3d *data, char **dup_map, int x, int y)
{
	dup_map[y][x] = '1';
	if (y - 1 >= 0 && dup_map[y - 1] && ((int)ft_strlen(dup_map[y - 1]) >= x))
	{
		if (dup_map[y - 1][x] == '0')
			dup_map[y - 1][x] = 'N';
		else if (dup_map[y - 1][x] == '1' || dup_map[y - 1][x] == 'S' || dup_map[y - 1][x] == 'N' || dup_map[y - 1][x] == 'E' || dup_map[y - 1][x] == 'W')
			;
		else
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	if (y + 1 < data->map.map_len_y && dup_map[y + 1] && ((int)ft_strlen(dup_map[y + 1]) >= x))
	{
		if (dup_map[y + 1][x] == '0')
			dup_map[y + 1][x] = 'S';
		else if (dup_map[y + 1][x] == '1' || dup_map[y + 1][x] == 'S' || dup_map[y + 1][x] == 'N' || dup_map[y + 1][x] == 'E' || dup_map[y + 1][x] == 'W')
			;
		else
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	if (x - 1 >= 0 && dup_map[y][x - 1])
	{
		if (dup_map[y][x - 1] == '0')
			dup_map[y][x - 1] = 'W';
		else if (dup_map[y][x - 1] == '1' || dup_map[y][x - 1] == 'S' || dup_map[y][x - 1] == 'N' || dup_map[y][x - 1] == 'E' || dup_map[y][x - 1] == 'W')
			;
		else
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	if (x + 1 < (int)ft_strlen(dup_map[y]) && dup_map[y][x + 1])
	{
		if (dup_map[y][x + 1] == '0')
			dup_map[y][x + 1] = 'E';
		else if (dup_map[y][x + 1] == '1' || dup_map[y][x + 1] == 'S' || dup_map[y][x + 1] == 'N' || dup_map[y][x + 1] == 'E' || dup_map[y][x + 1] == 'W')
			;
		else
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	find_treasure(t_cub3d *data, char **dup_map, int x, int y)
{
	if (y - 1 >= 0 && dup_map[y - 1] && ((int)ft_strlen(dup_map[y - 1]) >= x) && dup_map[y - 1][x] == 'T')
		return (EXIT_SUCCESS);
	if (y + 1 < data->map.map_len_y && dup_map[y + 1] && ((int)ft_strlen(dup_map[y + 1]) >= x) && dup_map[y + 1][x] != 'T')
		return (EXIT_SUCCESS);
	if (x - 1 >= 0 && dup_map[y][x - 1] && dup_map[y][x - 1] != 'T')
		return (EXIT_SUCCESS);
	if (x + 1 < (int)ft_strlen(dup_map[y]) && dup_map[y][x + 1] && dup_map[y][x + 1] != 'T')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static void	flood_fill_iter(t_cub3d *data, char **dup_map)
{
	int		x;
	int		y;

	x = find_pos(dup_map, 'x');
	y = find_pos(dup_map, 'y');
	while (x != 0 || y != 0)
	{
		if (BONUS && find_treasure(data, dup_map, x, y) == EXIT_SUCCESS)
			data->map.check.catch_treasure = true;
		if (apply_cross_player(data, dup_map, x, y) == EXIT_FAILURE)
		{
			data->map.check.invalid_map = true;
			return ;
		}
		x = find_pos(dup_map, 'x');
		y = find_pos(dup_map, 'y');
	}
}

int	algo_flood_fill(t_cub3d *data)
{
	if (data->map.map_len_y < 400)
		flood_fill_rec(data, data->map.dup_map, data->map.pos_x, data->map.pos_y);
	else
		flood_fill_iter(data, data->map.dup_map);
	if (data->map.check.invalid_map)
	{
		if (!BONUS)
			free_texture_paths(data->wall, 4);
		else
			free_texture_paths(data->wall, 12);
		exit_parsing(&data->map, "Error\nCub3D: map not close");
	}
	if (BONUS && data->map.check.catch_treasure == false)
	{
		free_texture_paths(data->wall, 12);
		exit_parsing(&data->map, "Error\nCub3D: treasure not reached");
	}
	return (EXIT_SUCCESS);
}
