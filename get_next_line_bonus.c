/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:48:50 by mymik             #+#    #+#             */
/*   Updated: 2019/11/19 14:55:53 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	index_of(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	handler(int fd, char **str, char **line)
{
	int ret;

	if (fd < 0 || !line || !BUFFER_SIZE || BUFFER_SIZE < 0)
		return (1);
	if (!str[fd])
	{
		if (!(str[fd] = malloc(BUFFER_SIZE + 1)))
			return (1);
		if ((ret = read(fd, str[fd], 1)) == -1)
			return (1);
		str[fd][ret] = '\0';
	}
	return (0);
}

static char	*next_buffer(int fd)
{
	char	*buffer;
	int		ret;

	buffer = malloc(BUFFER_SIZE + 1);
	if ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		return (buffer);
	}
	free(buffer);
	return (NULL);
}

void		join_and_free(char **str, char **buffer, char **line, int fd)
{
	char *tmp;

	tmp = str[fd];
	str[fd] = ft_strjoin(str[fd], *buffer);
	*line = str[fd];
	free(*buffer);
	free(tmp);
}

int			get_next_line(int fd, char **line)
{
	static char	*str[4864];
	char		*buffer;
	char		*tmp;
	int			i;

	if (handler(fd, str, line) == 1)
		return (-1);
	while ((i = index_of(str[fd], '\n')) == -1)
	{
		if (!(buffer = next_buffer(fd)))
		{
			return ((*str[fd]) ? 1 : 0);
		}
		join_and_free(str, &buffer, line, fd);
		*line = str[fd];
	}
	tmp = str[fd];
	*line = ft_substr(str[fd], 0, i);
	str[fd] = ft_strdup(&str[fd][i + 1]);
	free(tmp);
	return (1);
}
