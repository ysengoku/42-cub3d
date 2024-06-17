/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 09:18:05 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	animation_open(t_cub3d *data)
{
	int	j;

	j = 0;
	if (*i <= 3)
	{
		*i += 1;
		while (j < 90000000)
			j++;
	}
	if (*i > 3)
	{
		*i = 0;
		data->anim_open = false;
		data->map.map[(int)round(data->player.dir_y)
			+ (int)data->player.pos_y][(int)round(data->player.dir_x)
			+ (int)data->player.pos_x] = 'O';
	}
}

static void	animation_close(t_cub3d *data)
{
	int	j;

	j = 0;
	if (*i > 0)
	{
		*i -= 1;
		while (j < 90000000)
			j++;
	}
	else if (*i == 0)
		*i = 4;
	else
}

void	animations(t_cub3d *data)
{
	if (data->anim_open == true)
		animation_open(data);
	else if (data->anim_close == true)
		animation_close(data);
}

int	get_door_texture_paths(t_cub3d *data)
{
	if (!BONUS)
		return (0);
	data->wall[DR].path = ft_strdup(DOOR_TEX);
	data->wall[DR1].path = ft_strdup(DOOR_TEX1);
	data->wall[DR2].path = ft_strdup(DOOR_TEX2);
	data->wall[DR3].path = ft_strdup(DOOR_TEX3);
	if (!data->wall[DR].path)
	{
		free_texture_paths(data->wall, 8);
		exit_parsing(&data->map, "Error\nCub3D: malloc failed");
		return (1);
	}
	return (0);
}

void	switch_door_status(t_cub3d *data)
{
	int	target_x;
	int	target_y;

	target_x = (int)data->player.pos_x;
	target_y = (int)data->player.pos_y;
	if (data->player.dir_x > 0)
		target_x += round(data->player.dir_x);
	else if (data->player.dir_x < 0)
		target_x -= round(-data->player.dir_x);
	if (data->player.dir_y > 0)
		target_y += round(data->player.dir_y);
	else if (data->player.dir_y < 0)
		target_y -= round(-data->player.dir_y);
	if (data->map.map[target_y][target_x] == 'D')
		data->anim_open = true;
	else if (data->map.map[target_y][target_x] == 'O')
		data->anim_close = true;
}
