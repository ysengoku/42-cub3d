/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 11:51:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(t_cub3d *data, char *line)
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
	if (!path)
		return (exit_parsing(data, "malloc", true), NULL);
	free_split(ar);
	return (path);
}

int	get_sprites_path(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (ft_strncmp(data->map.data_map[i], "NO ", 3) == 0
			&& !data->wall[NO].path)
			data->wall[NO].path = get_path(data, data->map.data_map[i]);
		else if (ft_strncmp(data->map.data_map[i], "SO ", 3) == 0
			&& !data->wall[SO].path)
			data->wall[SO].path = get_path(data, data->map.data_map[i]);
		else if (ft_strncmp(data->map.data_map[i], "WE ", 3) == 0
			&& !data->wall[WE].path)
			data->wall[WE].path = get_path(data, data->map.data_map[i]);
		else if (ft_strncmp(data->map.data_map[i], "EA ", 3) == 0
			&& !data->wall[EA].path)
			data->wall[EA].path = get_path(data, data->map.data_map[i]);
		i++;
	}
	if (!data->wall[NO].path || !data->wall[SO].path
		|| !data->wall[WE].path || !data->wall[EA].path)
		return (EXIT_FAILURE);
	if (BONUS && get_door_and_treasure_texture_paths(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
