/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:53:45 by clems             #+#    #+#             */
/*   Updated: 2021/06/24 16:25:53 by clems            ###   ########.fr       */
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

#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_getjoin(char *line, char *buffer, size_t n)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = ft_calloc(ft_strlen(line) + n + 1, sizeof(char));
	if (!res)
		return ;
	i = 0;
	while (line[i])
	{
		res[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer[j] && n > 0)
	{
		res[i] = buffer[j];
		j++;
		i++;
		n--;
	}
	free (line);
	line = res;
}

char	*getcontent(int fd, char *line, char *buffer, size_t exit)
{
	int	stay;
	stay = 1;
	while (stay > 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		stay = read(fd, buffer, BUFFER_SIZE);
		if (stay < 0)
			return (NULL);
		exit = 0;
		while (exit < BUFFER_SIZE)
		{
			
			if (buffer[exit] == '\n')
				break ;
			exit++;
		}
		ft_getjoin(line, buffer, exit);
		if (!line)
			return (NULL);
		if (buffer[exit] == '\n')
			break ;
	}
	return (line);
}

// create the buffer memory, if it doesn't exist yet
// if it exists already that meand a line has ended within it, so skip over
// until \n and count either until the next \n or the end
// and alloc and copy into CL
// replace the first \n by something else so that the next funcion call doesn't
// trip on it
// if no second \n was found keep on reading
// if in any subfunction an end is found, exit is changed to indicate that



int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE];
	int			exit;
	int			i;
	int			c;
	int			j;

	exit = 1;


		i = 0;
		while (buffer[i] != '\n' && buffer[i])
			i++;
		buffer[i] = 'n';
		i++;
		c = 0;
		while (buffer[c + i] != '\n' && buffer[c + i])
			c++;
		*line = ft_calloc(c + 1, sizeof(char));
		j = 0;
		while (j < c)
		{
			*line[j] = buffer[j + i];
			j++;
		}
		j++;
		if (buffer[j + i - 1] == '\n')
			exit = 0;
	
	if (exit > 0)
		*line = getcontent(fd, *line, buffer, exit);
	*line = *line;
	return (ft_strlen(*line));
}

//int	get_next_line(int fd, char **line)
//{
//	size_t		BUFFER_SIZE = 32;
//	static char	*buffer;
//	int			exit;
//	int			i;
//	int			c;
//	int			j;
//
//	exit = 1;
//	if (!buffer)
//		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
//	else
//	{
//		i = 0;
//		while (buffer[i] != '\n' && buffer[i])
//			i++;
//		buffer[i] = 'n';
//		i++;
//		c = 0;
//		while (buffer[c + i] != '\n' && buffer[c + i])
//			c++;
//		*line = ft_calloc(c + 1, sizeof(char));
//		j = 0;
//		while (j < c)
//		{
//			*line[j] = buffer[j + i];
//			j++;
//		}
//		j++;
//		if (buffer[j + i - 1] == '\n')
//			exit = 0;
//	}
//	if (exit > 0)
//		*line = getcontent(fd, *line, buffer, exit);
//	*line = *line;
//	return (ft_strlen(*line));
//}



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
	}
	close(fd);
}
