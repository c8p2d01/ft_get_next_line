/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:53:45 by clems             #+#    #+#             */
/*   Updated: 2021/07/09 14:52:08 by clems            ###   ########.fr       */
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

// copy n bytes from src to dest and return dest while protecting against
// overlapping memory of src and dest
void	ft_memmove(void *dest, const void *src, size_t n)
{
	if (!(!dest || !src))
	{
		if ((size_t)src > (size_t)dest)
			ft_memcpy(dest, src, n);
		else
		{
			while (n--)
				((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
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

// concatenate two strings into one new string, replacing the first one
char	*ft_getjoin(char **s1, char const *s2, int end)
{
	size_t	total_length;
	size_t	length_dst;
	size_t	length_src;
	char	*temps;

	temps = ft_calloc(ft_strlen(*s1) + 1, 1);
	ft_memmove(temps, *s1, ft_strlen(*s1));
	length_dst = ft_strlen((char *)temps);
	length_src = ft_sublen((char *)s2);
	total_length = length_src + length_dst + 1 + end;
	ft_bzero(*s1, ft_strlen(*s1));
	free(*s1);
	*s1 = ft_calloc(total_length, 1);
	if (s1 == NULL)
		return (NULL);
	ft_memcpy(*s1, temps, length_dst + 1);
	ft_memcpy(&(*s1)[(length_dst)], s2, length_src);
	if (end)
		(*s1)[length_dst + length_src] = '\n';
	return (*s1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		**line;
	int			r;

	r = BUFFER_SIZE;
	line = (char **)ft_calloc(sizeof(**line), 1);
	*line = ft_calloc(sizeof(*line), 1);
	while (r == BUFFER_SIZE || ft_strlen(buffer))
	{
		if (buffer[0])
		{
			*line = ft_getjoin(line, buffer, 0);
			if (ft_sublen(buffer) != BUFFER_SIZE)
			{
				r = ft_sublen(buffer);
				ft_memmove(buffer, &buffer[r], ft_strlen(&buffer[r]));
				ft_bzero(&buffer[r], BUFFER_SIZE - r);
				break ;
			}
		}
		r = read(fd, &buffer[0], BUFFER_SIZE);
		if (r <= -1 || fd < 0 || (r == 0 && ft_strlen(buffer) == 0))
			return (NULL);
		buffer[r] = '\0';
	}
	return (ft_getjoin(line, "\n", 1));
}
//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 32
//#endif

//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>

//#define FILENAME "test"
//
//int    main (void)
//{
//    FILE    *fp = fopen(FILENAME, "r");
//    int        fd = fileno(fp);
//    printf("%d\n", fd);
//    int        x;
//
//	char *str;
//
//    x = 9;
//    while (x > 0)
//    {
//		str = get_next_line(fd);
//		write(1, str, ft_strlen(str) + 2);
//        x--;
//    }
//    return (x);
//}