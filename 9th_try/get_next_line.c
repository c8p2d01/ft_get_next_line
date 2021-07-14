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

#include "get_next_line.h"

// concatenate two strings into one new string, replacing the first one
char    *ft_strjoin(char *s1, char *s2)
{
    char    *tmp;

    tmp = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char)); // leak here ?
    if (!tmp)
        return (NULL);
    ft_memcpy(tmp, s1, ft_strlen(s1));
    ft_memcpy(tmp + ft_strlen(s1), s2, ft_strlen(s2));
    return (tmp);
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

void	ft_buffR(char *o_buffer, char *remainder)
{
	int	i;

	i = 0;
	while (remainder[i])
	{
		o_buffer[i] = remainder[i];
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		o_buffer[i] = '\0';
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*end;
	char		*tmp;
	int			r;

	line = ft_calloc(1, sizeof(char));
	r = BUFFER_SIZE;
	while (!ft_strchr(buffer, '\n') && r == BUFFER_SIZE)
	{
		tmp = ft_strjoin(line, buffer);
		free (line);
		line = tmp;
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		if (fd < 0 || r <= 0)
			return (NULL);
	}
	r = 0;
	while (buffer[r] != '\n' && buffer[r] != '\0')
		r++;
	end = ft_substr(buffer, 0, r);
	tmp = ft_strjoin(line, end);
	free (end);
	free (line);
	ft_buffR(buffer, &buffer[r] + 1);
	return (ft_strjoin(tmp, "\n"));
}
