/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:22:58 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/20 08:04:47 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(const char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen((char *)str);
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strjoin_gnl(char *buf, char *stash)
{
	char	*stash_join;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!buf || (!buf && !stash))
		return (NULL);
	if (!stash)
		return (ft_strdup_gnl(buf));
	i = 0;
	j = 0;
	len = ft_strlen(buf) + ft_strlen(stash);
	stash_join = (char *) malloc(sizeof(char) * (len + 1));
	if (!stash_join)
		return (NULL);
	while (stash[i])
	{
		stash_join[i] = stash[i];
		i++;
	}
	while (buf[j])
		stash_join[i++] = buf[j++];
	stash_join[len] = '\0';
	free(stash);
	return (stash_join);
}

char	*ft_extract_line_gnl(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	if (ft_verifn_gnl(stash) > 0 || stash[0] == '\n')
		j = ft_verifn_gnl(stash) + 1;
	else
		j = ft_strlen(stash);
	line = (char *)malloc(sizeof(char) * (j + 1));
	if (!line)
		return (NULL);
	line[j] = '\0';
	while (i < j)
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}

char	*ft_rebuild_stash_gnl(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	if (!stash)
		return (NULL);
	if (ft_verifn_gnl(stash) == 0 && stash[0] != '\n')
	{
		free(stash);
		return (ft_strdup_gnl("\0"));
	}
	else
	{
		i = ft_verifn_gnl(stash) + 1;
		j = 0;
		new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i) + 1);
		if (!new_stash)
			return (NULL);
		new_stash[(ft_strlen(stash) - i)] = '\0';
		while (stash[i])
			new_stash[j++] = stash[i++];
		free(stash);
		return (new_stash);
	}
}
