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
#define BUFFER_SIZE 32
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

//return a pointer to the first instance of c in str
// return NULL if the caharcter wasn't found ☺
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}



// calculate the correct return value and ggf process line and buffer:
// after safety checks and errors
// alloc and copy over the remainder
// alloc and copy over the line
// free buffer and insert the remainder
int result(int fd, int r, char *b, char **line)
{
	char *tmp;

	if(fd < 0 || r == -1)
		return (-1);
	if(r == 0 && b == NULL)
	{
		*line = ft_calloc(1, 1);
		return (0);
	}
	tmp = ft_calloc(ft_strlen(ft_strchr(b, '\n')) + 1, sizeof(char));
	tmp = ft_memcpy(tmp, ft_strchr(b, '\n') + 1, ft_strlen(ft_strchr(b, '\n')));
	*line = ft_calloc(ft_strlen(b) - ft_strlen(tmp) + 1, sizeof(char));
	*line = ft_memcpy(*line, b, (ft_strlen(b) - ft_strlen(tmp) - 1));
	free (b);
	b = ft_calloc(ft_strlen(tmp), sizeof(char));
	b = ft_memcpy(b, tmp, ft_strlen(tmp));
	free (tmp);
	return (ft_strlen(*line));
}

int get_next_line(int fd, char **line)
{
	static char *b;
	int r;
	int i;
	int f;
	char *temp;

	i = 0;
	f = 0;
	if (b)
		f = 1;
	r = BUFFER_SIZE;
	while (r)
	{
		if (i > 0 || f)
		{
			temp = ft_calloc(ft_strlen(b) + 1, sizeof(char));
			temp = (char *)ft_memcpy(temp, b, ft_strlen(b));
		}
		free (b);
		b = ft_calloc(BUFFER_SIZE * (i + 1) + 1, sizeof(char));
		if (i > 0 || f)
		{
			b = ft_memcpy(b, temp, ft_strlen(temp));
			free (temp);
		}
		r = read(fd, &b[BUFFER_SIZE * i], BUFFER_SIZE);
		if (ft_strchr(b, '\n'))
			break ;
		i++;
	}
	return (result(fd, r, b, line));
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
