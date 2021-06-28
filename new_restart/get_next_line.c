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

// allocate memory that consists only of '\0' bytes
void	*ft_calloc(size_t nmemb, size_t n)
{
	void	*dest;
	size_t	i;

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

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	    return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

// copy n bytes from src to dest and return dest
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

// copy n bytes from src to dest and return dest while protecting against
// overlapping memory of src and dest
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t tn;

	tn = n;
	if (!dest || !src)
		return (NULL);
	if ((size_t)src > (size_t)dest)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	while (tn < BUFFER_SIZE)
	{
		((unsigned char *)dest)[tn] = '\0';
		tn++;
	}
	return (dest);
}

// copy size byttes from src to dest, overwriting dest
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
	    return (0);
	while (src[i] && (i + 1) < size && src[i] != '\n')
	{
		if (!(size == 0))
			dst[i] = src[i];
		i++;
	}
	if (!(size == 0))
		dst[i] = '\0';
	return (ft_strlen((char *)src));
}

// concatenate two strings into one new string
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_length;
	size_t	length_dst;
	size_t	length_src;
	char	*res;

	length_dst = ft_strlen((char *)s1);
	length_src = ft_strlen((char *)s2);
	total_length = length_src + length_dst;
	res = malloc(total_length + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, length_dst + 1);
	ft_strlcpy(&res[(length_dst)], s2, length_src + 1);
	if (length_src < BUFFER_SIZE)
		ft_memmove((char *)s2, (s2 + length_src + 1), (BUFFER_SIZE - length_src + 1));
	return (res);
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

int	get_next_line(int fd, char **line)
{
	static char	*buffer;
	int			nread;

	nread = BUFFER_SIZE + 1;
	//*line = ft_calloc(1, 1);
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0)
	{
		free (line);
		return (-1);
	}
	while (nread > 0)
	{
	    if (nread != BUFFER_SIZE + 1)
	        ft_bzero(buffer, BUFFER_SIZE + 1);
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread == -1)
		{
			free (line);
			return (-1);
		}
		*line = ft_strjoin(*line, ft_substr(buffer, 0, ft_strlen(buffer)));
		if (ft_strlen(buffer) != BUFFER_SIZE)
			break ;
	}
	return (ft_strlen(buffer));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	write(fd, "\n", 1);
}

int main(void)
{
	int fd;
	fd = open("test", O_RDWR | O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
	char *str;
// size_t		BUFFER_SIZE = 32;//comment this out before compiling
//	ft_putendl_fd("                  /´¯/)         ", fd);
//	ft_putendl_fd("                ,/¯  /          ", fd);
//	ft_putendl_fd("               /    /           ", fd);
//	ft_putendl_fd("          /´¯/'   '/´¯¯`·¸      ", fd);
//	ft_putendl_fd("      /'/   /    /       /¨¯\\   ", fd);
//	ft_putendl_fd("     ('(   ´   ´     ¯~/'   ')  ", fd);
//	ft_putendl_fd("     \\                 '   /  ", fd);
//	ft_putendl_fd("      ''   \\           _.·´     ", fd);
//	ft_putendl_fd("        \\              (        ", fd);
//	ft_putendl_fd("          \\             \\       ", fd);
//	ft_putendl_fd("", fd);

	for (int i = 0; i < 10; i++)
	{
		get_next_line(fd, &str);
		printf("%d %s\n",(i + 1), str);
		free (str);
	}
	close(fd);
}
