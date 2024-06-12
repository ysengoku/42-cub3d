/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:25:44 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/12 14:49:36 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_all(t_cub3d *data, int status)
{
	int	i;

	i = 0;
	while (i < 5) // if not bonus, while (i < 4)
	{
		if (data->wall[i].img)
			mlx_destroy_image(data->mlx_ptr, data->wall[i].img);
		free(data->wall[i].path);
		i++;
	}
	if (data->mmap.img.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
	if (data->doors)
		free(data->doors);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_data_map(&data->map);
	return (status);
}
