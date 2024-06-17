/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 11:34:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	animation_open(t_cub3d *data)
{
	int	j;

	j = 0;
	if (data->animation == 3)
	{
		while (j < 90000000)
			j++;
		data->animation = 0;
		data->anim_open = false;
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'O';
	}
	else
	{
		while (j < 90000000)
			j++;
		(data->animation)++;
	}
}

static void	animation_close(t_cub3d *data)
{
	int	j;

	j = 0;
	if (data->animation == 0)
	{
		while (j < 90000000)
			j++;
		data->anim_close = false;
	}
	else
	{
		while (j < 90000000)
			j++;
		(data->animation)--;
	}
}

void	animations(t_cub3d *data)
{
	if (data->anim_open == true && data->animation >= -1 && data->animation < 4)
		animation_open(data);
	else if (data->anim_close == true
		&& data->animation >= 0 && data->animation < 5)
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
	t_vector	target;

	target.x = data->player.pos.x;
	target.y = data->player.pos.y;
	if (data->player.dir.x > 0)
		target.x += round(data->player.dir.x);
	else if (data->player.dir.x < 0)
		target.x -= round(-data->player.dir.x);
	if (data->player.dir.y > 0)
		target.y += round(data->player.dir.y);
	else if (data->player.dir.y < 0)
		target.y -= round(-data->player.dir.y);
	if (data->map.map[(int)target.y][(int)target.x] == 'D')
	{
		data->animation = -1;
		data->anim_open = true;
	}
	else if (data->map.map[(int)target.y][(int)target.x] == 'O')
	{
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'D';
		data->animation = 4;
		data->anim_close = true;
	}
}
