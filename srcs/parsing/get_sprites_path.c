/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/14 16:39:08 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(char *line)
{
	char	**ar;
	char	*path;
	int		i;

	if (!line)
		return (NULL);
	path = NULL;
	i = 0;
	ar = ft_split(line, ' ');
	if (!ar)
		return (NULL);
	while (ar[i])
		i++;
	if (i != 2)
		return (free_split(ar), NULL);
	path = ft_strdup(ar[1]);
	free_split(ar);
	return (path);
}

static char	*get_sprite_path(char *sprite, t_map *data_map)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data_map->data_map[i])
	{
		if (ft_strncmp(data_map->data_map[i], sprite, 2) == 0)
		{
			path = get_path(data_map->data_map[i]);
			break ;
		}
		i++;
	}
	return (path);
}

int	get_sprites_path(t_cub3d *data)
{
	int	i;

	i = 0;
	data->wall[NO].path = get_sprite_path("NO", &data->map);
	data->wall[SO].path = get_sprite_path("SO", &data->map);
	data->wall[WE].path = get_sprite_path("WE", &data->map);
	data->wall[EA].path = get_sprite_path("EA", &data->map);
	if (!data->wall[NO].path || !data->wall[SO].path
		|| !data->wall[WE].path || !data->wall[EA].path)
	{
		free_texture_paths(data->wall, 4);
		exit_parsing(&data->map, "Error\nCub3D: invalid sprite");
		return (EXIT_FAILURE);
	}
	/*=== Bonus =================================================*/
	if (BONUS)
	{
		if (get_door_texture_paths(data) == 1)
			return (1);
	// if (!data->wall[DR].path)
	// {
	// 	free_texture_paths(data->wall, 4);
	// 	exit_parsing(&data->map, "Error\nCub3D: malloc failed");
	// 	return (EXIT_FAILURE);
	// }
	}
	/*=============================================================*/
	return (EXIT_SUCCESS);
}
