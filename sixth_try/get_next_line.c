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

#include <get_next_line.h>

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

// Notes to make this more understandable:
// we need to allocate emmory for a portion of the string starting at start
// the length is given but first a few checks
// 1	if there is no soulce return NULL
// 2	if the start is outside the string, return an empty string
// 3	if the remaining length after start is smaller than len, continue
// else	make the leen-sub to the longes remaining possible
// then allocate and copy over
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
	ft_memcpy(res, &s[start], lsub);
	return (res);
}

// concatenate two strings into one new string, replacing the first one
char	*ft_getjoin(char **s1, char const *s2)
{
	size_t	total_length;
	size_t	length_dst;
	size_t	length_src;
	char	*temps;

	temps = ft_substr(*s1, 0, ft_strlen(*s1));
	length_dst = ft_strlen((char *)temps);
	length_src = ft_sublen((char *)s2);
	total_length = length_src + length_dst + 1;
	free(*s1);
	*s1 = NULL;
	*s1 = ft_calloc(total_length, sizeof(char));
	if (s1 == NULL)
		return (NULL);
	ft_memcpy(*s1, temps, length_dst + 1);
	ft_memcpy(&(*s1)[(length_dst)], s2, length_src);
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
			*line = ft_getjoin(line, buffer);
			if (ft_strchr(buffer, '\n'))
			{
				ft_memmove(buffer, ft_strchr(buffer, '\n') + 1, \
											BUFFER_SIZE - ft_sublen(buffer));
				break ;
			}
		}
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1 || fd < 0 || (r == 0 && ft_strlen(buffer) == 0))
			return (NULL);
		buffer[r] = '\0';
	}
	return (*line);
}
//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 32
//#endif
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//
//// sets n bytes of "s" to the value '\0'
//void	ft_bzero(void *s, size_t n)
//{
//	size_t	i;
//
//	i = 0;
//	while (i < n)
//	{
//		((char *)s)[i] = '\0';
//		i++;
//	}
//}
//
//#define FILENAME "test"
//
//int    main (void)
//{
//    FILE    *fp = fopen(FILENAME, "r");
//    int        fd = fileno(fp);
//    printf("%d\n", fd);
//    int        x;
//
//    x = 8;
//    while (x > 0)
//    {
//        printf("%d : %s\n", x, get_next_line(fd));
//        x--;
//    }
//    return (x);
//}
