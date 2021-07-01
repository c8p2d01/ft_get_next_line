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

char	*ft_stepbuffer(char *s, size_t i)
{
	char	*dest;

	dest = ft_calloc(ft_strlen((char *)s) + 1 + (i * BUFFER_SIZE), 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, ft_strlen((char *)s) + 1);
	return (dest);
}

int get_next_line(int fd, char **line)
{
	static char	*buffer;
	char		*temp;
	int			nread;
	int			i;

	nread = 1;
	i = 0;
	while (nread)
	{
		temp = ft_stepbuffer(buffer, i);
		free(buffer);
		buffer = temp;
		nread = read(fd, &buffer[(BUFFER_SIZE * i)], BUFFER_SIZE);
		if
	}
	return (ft_linelen(*line));
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
