/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:02:23 by mymik             #+#    #+#             */
/*   Updated: 2019/12/17 15:03:52 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		get_line(char **str, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *str;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	*line = ft_substr(tmp, 0, i);
	if (!tmp[i])
	{
		*str = NULL;
		free(tmp);
		return (0);
	}
	*str = ft_strdup(&tmp[i + 1]);
	free(tmp);
	if (!*line || !*str)
		return (-1);
	if (*str != NULL)
		return (1);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[265];
	char		*buffer;
	int			ret;
	char		*tmp;

	if (fd < 0 || fd > 256 || !line || BUFFER_SIZE <= 0
			|| !(buffer = malloc(BUFFER_SIZE + 1)) || read(fd, buffer, 0) == -1)
		return (-1);
	if (!str[fd])
		if (!(str[fd] = ft_strdup("\0")))
			return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		tmp = str[fd];
		str[fd] = ft_strjoin(str[fd], buffer);
		free(tmp);
		if (index_of(str[fd], '\n') != -1)
			break ;
	}
	free(buffer);
	return (get_line(&str[fd], line));
}
