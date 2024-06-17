/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 11:56:15 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_data(t_cub3d *data, t_player *player, t_map *map)
{
	player->pos_x = map->pos_x;
	player->pos_y = map->pos_y;
	player->dir_degree = (double)map->p_dir;
	data->ceiling_color = convert_color(data->map.c_rgb);
	data->floor_color = convert_color(data->map.f_rgb);
}

int	set_wall_texture(t_cub3d *data, t_xpm_img *wall)
{
	int		i;
	int		n;

	i = -1;
	if (!BONUS)
		n = 4;
	else
		n = 11;
	while (++i < n)
	{
		wall[i].img = mlx_xpm_file_to_image(data->mlx_ptr, wall[i].path,
				&wall[i].w, &wall[i].h);
		if (wall[i].img == NULL)
		{
			while (i-- > 0)
				mlx_destroy_image(data->mlx_ptr, wall[i].img);
			while (++i < n)
				free(wall[i].path);
			clear_data(data);
			ft_perror_exit("MLX", 1);
		}
		wall[i].addr = mlx_get_data_addr(wall[i].img,
				&wall[i].bpp, &wall[i].line_len, &wall[i].endian);
	}
	return (0);
}
