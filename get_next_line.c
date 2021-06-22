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

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_getjoin(char *s1, char *s2, size_t n)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && n > 0)
	{
		res[i] = s2[j];
		j++;
		i++;
		n--;
	}
	//free(s1);
	return (res);
}

// getrest has a few interesting cases; if there is more than one line ending 
// the function should not read again but end and give the even next line when
// called again. therefore i look throught the buffer for the \n and count
// until the buffer ended or there is another \n, then i alloc that amout and
// copy the segment but also change the first \n to something else, so that the
// next function call skips the current segment.

void	ft_getrest(char *res, char *temp, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
		res = ft_calloc(1, sizeof(char));
	else
	{
		temp[i] = 'N';
		i++;
		k = i;
		while (temp[k] && temp[k] != '\n')
			k++;
		res = ft_calloc(k - i + 1, sizeof(char));
		j = 0;
		while (i < k)
		{
			res[j] = temp[i];
			i++;
			j++;
		}
		if (k != BUFFER_SIZE)
			n = -1;
	}
	
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

char	*getcontent(int fd, char *res, char *temp, size_t n)
{
	size_t	stay;

	stay = 1;
	while (stay > 0)
	{
		ft_bzero(temp, BUFFER_SIZE);
		stay = read(fd, temp, BUFFER_SIZE);
		n = 0;
		while (n < BUFFER_SIZE)
		{
			if (temp[n] == '\n')
				break ;
			n++;
		}
		res = ft_getjoin(res, temp, n);
		if (!res)
			return (NULL);
		if (temp[n] == '\n')
			break ;
	}
	return (res);
}

//temp is the bufferlengthcharacters of read
//res is the string into which the temps are concatenated
//n is for one a couter in subfunctions but also an indicator if the
//leftover chars from the previous calls lead to an EOL so that we mustn't Read

int	get_next_line(int fd, char **line)
{
	static char	*temp;
	char		*res;
	size_t		n;

	n = 0;
	res = ft_calloc(1, sizeof(char));
	if (!temp)
		temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	ft_getrest(res, temp, n);
	if (!temp)
		return (-1);
	if (n >= 0)
		res = getcontent(fd, res, temp, n);
	if (!res)
		return (-1);
	*line = res;
	return (ft_strlen(res));
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	for (int i = 0; i < 5; i++)
	{
		get_next_line(fd, &str);
		printf("%d %s\n",(i + 1), str);
	}
	close(fd);
}
