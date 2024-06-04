/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:02:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/04 08:25:36 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_window(t_cub3d *data)
{
	int	i;

	mlx_destroy_image(data->mlx_ptr, data->img.img);
	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->wall[i].img);
		free(data->wall[i].path);
		i++;
	}
	if (data->mmap.img.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
	if (data->mmap.floor.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.floor.img);
	if (data->mmap.player.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.player.img);
	if (data->mmap.wall.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.wall.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_mapdata(&data->map); // To check
	// free_data_map(&data->map);
	//------ free other things if needed -----
	exit(0);
}
