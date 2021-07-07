/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:53:45 by clems             #+#    #+#             */
/*   Updated: 2021/07/06 15:49:26 by clems            ###   ########.fr       */
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
#define BUFFER_SIZE 31
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// return the length of the given string;
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

size_t ft_sublen(char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\n' && s[i])
		i++;
	return (i);
}

// copy size bytes from src to dest, overwriting dest
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src && dst)
	{
	while (src[i] && (i + 1) < size)
	{
		if (!(size == 0))
			dst[i] = src[i];
		i++;
	}
	if (!(size == 0))
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

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

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	while (i < BUFFER_SIZE)
	{
	    ((unsigned char *)dest)[i] = '\0';
	    i++;
	}
	return (dest);
}

// sets n bytes of "s" to the value '\0'
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

//return a pointer to the first instance of c in str
// return NULL if the caharcter wasn't found ☺
char *ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

// create a duplicate string of s
char	*ft_strdup(const char *s, size_t extramem)
{
	char	*dest;

	dest = ft_calloc(ft_strlen((char *)s) + extramem + 1, 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, ft_strlen((char *)s) + 1);
	return (dest);
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



char *get_next_line(int fd)
{
	static char *buffer;
	char *line;
	char *tmp;
	int r;

	r = BUFFER_SIZE;
	while (r == BUFFER_SIZE)
	{
		buffer = ft_strdup(buffer, BUFFER_SIZE);
		if (ft_strchr(buffer, '\n'))
			break ;
		r = read(fd, &buffer[ft_strlen(buffer)], BUFFER_SIZE);
		if (r == 0 && ft_strlen(buffer) == 0 || r == - 1|| fd < 0)
		    return (NULL);
		if (ft_strchr(buffer, '\n') || r == 0 && ft_strlen(buffer) != 0)
			break ;
	}
	line = ft_substr(buffer, 0, ft_sublen(buffer));
    if (r == BUFFER_SIZE)
	{
	    tmp = ft_strdup(ft_strchr(buffer, '\n') + 1, 0);
	    ft_bzero(buffer, ft_strlen(buffer));
	    free (buffer);
    	buffer = ft_strdup(tmp, 0);
    	ft_bzero(tmp, ft_strlen(tmp));
    	if (tmp)
    	    free (tmp);
	}
	if (r == 0 && ft_strlen(buffer) != 0)
	    free (buffer);
	return (line);
}

int main(void)
{
	int fd;
	fd = open("test", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	char *str;
	while (1 > 0)
	{
		str = get_next_line(fd);
		if (str != NULL)
		{
		    printf("%s\n", str);
		    ft_bzero(str, ft_strlen(str));
		    free (str);
		}
		else
			break;
	}
	close(fd);
}
