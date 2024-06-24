/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:22:55 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 13:52:51 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_line(int fd, char *buf);
static char	*ft_append_buf(char *stash, char *buf);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			line_len;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_read_line(fd, buf);
	if (!line)
		return (NULL);
	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		line_len = newline - line + 1;
		ft_strlcpy(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		line_len = ft_strlen(line);
		ft_strlcpy(buf, "", BUFFER_SIZE + 1);
	}
	line[line_len] = '\0';
	return (line);
}

static char	*ft_read_line(int fd, char *buf)
{
	ssize_t	read_size;
	char	*line;

	line = ft_strdup(buf);
	if (!line)
		return (NULL);
	read_size = 1;
	while (read_size > 0 && !ft_strchr(buf, '\n'))
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		buf[read_size] = '\0';
		if (read_size == 0 || read_size == -1)
			return (free(line), NULL);
		line = ft_append_buf(line, buf);
		if (!line)
			break ;
	}
	return (line);
}

static char	*ft_append_buf(char *line, char *buf)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(tmp, buf);
	free(tmp);
	tmp = NULL;
	if (!line)
		return (NULL);
	return (line);
}
// size_t	ft_verifn_gnl(char	*stash)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!stash)
// 		return (0);
// 	while (stash[i])
// 	{
// 		if (stash[i] == '\n')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_error_gnl(char **buf, char **stash)
// {
// 	if (!*buf && *stash)
// 	{
// 		free(*stash);
// 		*stash = NULL;
// 		return (NULL);
// 	}
// 	else if (!*stash && *buf)
// 	{
// 		free(*buf);
// 		*buf = NULL;
// 		return (NULL);
// 	}
// 	else if (!*buf && !*stash)
// 		return (NULL);
// 	else
// 	{
// 		free(*buf);
// 		*buf = NULL;
// 		free(*stash);
// 		*stash = NULL;
// 		return (NULL);
// 	}
// }

// char	*get_next_line(int fd)
// {
// 	static char		*stash = NULL;
// 	char			*buf;
// 	char			*next_line;
// 	static ssize_t	len_read = 0;

// 	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	if (!buf || fd == -1 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
// 		return (ft_error_gnl(&buf, &stash));
// 	while (!ft_verifn_gnl(stash))
// 	{
// 		len_read = read(fd, buf, BUFFER_SIZE);
// 		if (len_read == -1)
// 			return (ft_error_gnl(&buf, &stash));
// 		buf[len_read] = '\0';
// 		stash = ft_strjoin_gnl(buf, stash);
// 		if (len_read == 0)
// 			break ;
// 	}
// 	if (len_read == 0 && stash[0] == '\0')
// 		return (ft_error_gnl(&buf, &stash));
// 	free(buf);
// 	next_line = ft_extract_line_gnl(stash);
// 	stash = ft_rebuild_stash_gnl(stash);
// 	return (next_line);
// }
