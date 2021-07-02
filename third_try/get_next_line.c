/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:53:45 by clems             #+#    #+#             */
/*   Updated: 2021/06/07 18:08:05 by clems            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	Goal: return the adress of the start of the complete next line from fd
//
//	strategy?
//	read from fd into buffer
//	check if \n was encountered
//	append to string
//	repeat with new starting position
//	line 19 is wrong
//	make the read buffer static otherwise the leftover bytes are lost in the buf
//
//
//	Notes
//	read() starts where the last read() ended

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// allocate memory that consists only of '\0' bytes
void *ft_calloc(size_t nmemb, size_t n)
{
	void *dest;
	size_t i;

	dest = malloc(nmemb * n);
	if (!dest)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = '\0';
		i++;
	}
	return (dest);
}

size_t ft_strlen(char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i])
		i++;
	return (i);
}

//return a pointer to the first instance of c in str
char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	*f;

	f = (unsigned char *)str;
	i = 0;
	while (f[i])
	{
		if (f[i] == c)
			return ((char *)(f + i));
		i++;
	}
	if (f[i] == c)
		return ((char *)(f + i));
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size)
	{
		dst[i] = src[i];
	//	printf("%c\t%c\n", src[i], dst[i]);
		i++;
	}
	return (ft_strlen((char *)src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	lsub;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen((char *)s) <= start)
		return (ft_calloc(1, 1));
	else if ((size_t)((int)ft_strlen((char *)s) - start) > len)
		lsub = len;
	else
		lsub = (size_t)((int)ft_strlen((char *)s) - start);
	res = ft_calloc(lsub + 1, 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, &s[start], len);
	return (res);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dst;

	len = ft_strlen((char *)src) + 1;
	dst = ft_calloc((len) + 1, 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, src, len);
	return (dst);
}

char	*ft_stepbuffer(char *prev, size_t i, size_t offset)
{
	char	*new;

		printf("%s\t", &prev[offset]);
	new = ft_calloc(((i + 1) * BUFFER_SIZE) + 1, 1);
	if (new == NULL)
		return (NULL);
	if (prev)
	{
		printf("%s\t", &prev[offset]);
		ft_strncpy(new, &prev[offset], BUFFER_SIZE);
	}
	printf("%s\t", new);
	return (new);
}

int	rvalue(char *buffer,char **line, int nread,int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	if(fd < 0 || nread == -1)
		return (-1);
	if(nread == 0 && buffer == NULL)
	{
		*line = ft_calloc(1, 1);
		return (0);
	}
	else
	{
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
		{
			*line = ft_substr(buffer, 0, i);
			tmp = ft_stepbuffer(buffer, 0, i);
			if (buffer != NULL)
				free(buffer);
			buffer = ft_strdup(tmp);
			free (tmp);
			return (ft_strlen(*line));
		}
		else
		{
			*line = ft_strdup(buffer);
			return (0);
		}
	}
}

int get_next_line(int fd, char **line)
{
	static char	*buffer;
	char		*temp;
	int			nread;
	int			i;

	nread = 1;
	i = 0;
	if (!buffer)
      buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	while (nread)
	{
		temp = ft_stepbuffer(buffer, i, 0);
		if (buffer)
			free(buffer);
		buffer = ft_strdup(temp);
		free (temp);
		nread = read(fd, &buffer[(BUFFER_SIZE * i)], BUFFER_SIZE);
		if (ft_strchr(buffer, '\n'))
			break ;
		i++;
	}
	return (rvalue(buffer, line, nread, fd));
}

int main(void)
{
	int fd;
	fd = open("test", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	char *str;
	while (get_next_line(fd, &str))
	{
		printf("%s\n", str);
	}
	close(fd);
}
