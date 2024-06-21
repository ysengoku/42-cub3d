/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/21 18:50:20 by yusengok         ###   ########.fr       */
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

static void	treat_path(t_cub3d *data, char *line,  char *str)
{
	int	index;

	if (ft_strncmp(str, "NO", 3) == 0)
		index = 0;
	else if (ft_strncmp(str, "SO", 3) == 0)
		index = 1;
	else if (ft_strncmp(str, "WE", 3) == 0)
		index = 2;
	else if (ft_strncmp(str, "EA", 3) == 0)
		index = 3;
	data->wall[index].path = get_path(line);
}

int	get_sprites_path(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (ft_strncmp(data->map.data_map[i], "NO ", 3) == 0)
			treat_path(data, data->map.data_map[i], "NO");
		else if (ft_strncmp(data->map.data_map[i], "SO ", 3) == 0)
			treat_path(data, data->map.data_map[i], "SO");
		else if (ft_strncmp(data->map.data_map[i], "WE ", 3) == 0)
			treat_path(data, data->map.data_map[i], "WE");
		else if (ft_strncmp(data->map.data_map[i], "EA ", 3) == 0)
			treat_path(data, data->map.data_map[i], "EA");
		i++;
	}
	if (!data->wall[NO].path || !data->wall[SO].path
		|| !data->wall[WE].path || !data->wall[EA].path)
	{
		free_texture_paths(data->wall, 4);
		exit_parsing(&data->map, "Error\nCub3D: invalid sprite");
	}
	if (BONUS)
		get_door_and_treasure_texture_paths(data);
	return (EXIT_SUCCESS);
}
