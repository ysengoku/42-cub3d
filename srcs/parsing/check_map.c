/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:59:04 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 11:46:18 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_player(t_cub3d *data, int *i, int j)
{
	data->map.map[j][*i] = 'P';
	data->map.player = data->map.dup_map[j][*i];
	data->map.pos_x = *i;
	data->map.pos_y = j;
	data->map.check.player += 1;
	*i += 1;
}

static int	check_map_closed(t_cub3d *data, int *i, int j)
{
	if (j - 1 < 0 || *i >= (int)ft_strlen(data->map.dup_map[j - 1])
		|| ft_isalnum(data->map.dup_map[j - 1][*i]) == 0)
		return (EXIT_FAILURE);
	if (!data->map.dup_map[j + 1]
		|| *i >= (int)ft_strlen(data->map.dup_map[j + 1])
		|| ft_isalnum(data->map.dup_map[j + 1][*i]) == 0)
		return (EXIT_FAILURE);
	if (*i + 1 >= (int)ft_strlen(data->map.dup_map[j])
		|| ft_isalnum(data->map.dup_map[j][*i + 1]) == 0)
		return (EXIT_FAILURE);
	if (*i - 1 < 0 || ft_isalnum(data->map.dup_map[j][*i - 1]) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_char(t_cub3d *data, int *i, int j)
{
	if (data->map.dup_map[j][*i] == 'N' || data->map.dup_map[j][*i] == 'S'
		|| data->map.dup_map[j][*i] == 'E' || data->map.dup_map[j][*i] == 'W')
		assign_player(data, i, j);
	else if (data->map.dup_map[j][*i] == '0')
	{
		if (check_map_closed(data, i, j) == EXIT_FAILURE)
			return (exit_parsing(data, "map not close", false));
		*i += 1;
	}
	else if (data->map.dup_map[j][*i] == '1' || data->map.dup_map[j][*i] == 32)
		*i += 1;
	else if (BONUS && (data->map.dup_map[j][*i] == 'D'
		|| data->map.dup_map[j][*i] == 'T'))
	{
		if (data->map.dup_map[j][*i] == 'T')
		{
			data->map.check.treasure += 1;
			data->treasure.map.x = (double)*i + 0.5;
			data->treasure.map.y = (double)j + 0.5;
		}
		*i += 1;
	}
	else
		return (exit_parsing(data, "bad char in map detected", false));
	return (EXIT_SUCCESS);
}

int	check_valid_char(t_cub3d *data)
{
	int			i;
	int			j;

	j = -1;
	while (data->map.dup_map[++j])
	{
		i = 0;
		while (data->map.dup_map[j][i])
			if (check_char(data, &i, j) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	if (data->map.check.player != 1)
		return (exit_parsing(data, "invalid number of player", false));
	if (data->map.pos_x == 0 || data->map.pos_y == 0
		|| data->map.pos_y == data->map.map_len_y - 1)
		return (exit_parsing(data, "invalid player", false));
	if (data->map.dup_map[data->map.pos_y][data->map.pos_x] == 'N')
		data->map.p_dir = N;
	else if (data->map.dup_map[data->map.pos_y][data->map.pos_x] == 'S')
		data->map.p_dir = S;
	else if (data->map.dup_map[data->map.pos_y][data->map.pos_x] == 'E')
		data->map.p_dir = E;
	else if (data->map.dup_map[data->map.pos_y][data->map.pos_x] == 'W')
		data->map.p_dir = W;
	return (EXIT_SUCCESS);
}

int	check_map(t_cub3d *data)
{
	if (check_valid_char(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (BONUS && data->map.check.treasure != 1)
		return (exit_parsing(data, "invalid number of treasure", false));
	if (BONUS && apply_flood_fill(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
