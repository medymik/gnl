#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	if ((!dst && !src))
		return (NULL);
	if (src == dst)
		return (dst);
	s = (unsigned char*)src;
	d = dst;
	while (n--)
	{
		*(d++) = *(s++);
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if (src == dst)		
		return (dst);
	else if (dst > src)
	{
		while (len--)
		{
			*(unsigned char*)(dst + len) = *(unsigned char*)(src + len);
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;
	size_t	ls;

	if (!s1 || !s2)
		return (NULL);
	ls1 = strlen(s1);
	ls2 = strlen(s2);
	ls = ls1 + ls2;
	str = (char*)malloc(sizeof(char) * (ls + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, ls1);
	ft_memmove(str + ls1, s2, ls2);
	str[ls] = '\0';
	return (str);
}

int	index_of(char *str, char c)
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

int	handler(int fd, char **str, char **line)
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

char	*next_buffer(int fd)
{
	char *buffer;
	int ret;

	buffer = malloc(BUFFER_SIZE + 1);
	if ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		return (buffer);
	}
	free(buffer);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*r;
	char	*p;
	size_t	lens;

	if (!s)
		return (NULL);
	lens = ft_strlen(&s[start]);
	if (start > ft_strlen(s))
		return (strdup(""));
	lens = (lens <= len) ? lens : len;
	str = (char*)malloc(sizeof(char) * (lens + 1));
	if (!str)
		return (NULL);
	r = str;
	p = (char*)(s + start);
	if (str)
	{
		while (lens-- && *p)
		{
			*(str++) = *(p++);
		}
		*str = '\0';
	}
	return (r);
}

void	join_and_free(char **str, char **buffer, char **line)
{
	char *tmp;

	tmp = *str;
	*str = ft_strjoin(*str, *buffer);
	*line = *str;
	free(*buffer);
	free(tmp);
}

int	get_next_line(int fd, char **line)
{
	static char *str[4000];
	char *buffer;
	char *tmp;
	int i = 0;

	if (handler(fd, str, line) == 1)
		return (-1);
	while ((i = index_of(str[fd], '\n')) == -1)
	{
		//buffer = next_buffer(fd);
		if (!(buffer = next_buffer(fd)))
		{
			*line = strdup(str[fd]);
			free(str[fd]);
			return (0);
		}
		join_and_free(&str[fd], &buffer, line);
	}
	tmp = str[fd];
	*line = ft_substr(&str[fd][0], 0, i);
	str[fd] = strdup(&str[fd][i + 1]);
	free(tmp);
	return (1);
}
/*
int	main(int argc, char **argv)
{
	char *line = NULL;
	int fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		write(1, line, strlen(line));
		write(1, "\n", 1);
		free(line);
	}
	return (0);
}*/
