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
    ft_memcpy(&(tmp[ft_strlen(s1)]), s2, ft_strlen(s2));
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
	ft_memcpy(res, &s[start], lsub);
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

char	*freejoin(char *line, char *buffer, int opt)
{
	char	*tmp;
	char	*end;
	int		r;

	if (opt == -10)
	{
		tmp = ft_strjoin(line, buffer);
		free (line);
		line = tmp;
		return (line);
	}
	else
	r =	0;
	while (buffer[r] != '\n' && buffer[r] != '\0')
		r++;
	end = ft_substr(buffer, 0, r + 1);
	tmp = ft_strjoin(line, end);
	free (line);
	free (end);
	line = tmp;
	ft_buffR(buffer, &buffer[r] + 1);
	if (opt == 0)
		ft_bzero(buffer, BUFFER_SIZE);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			r;

	line = ft_calloc(1, sizeof(char));
	r = BUFFER_SIZE;
	while (!ft_strchr(buffer, '\n') && r == BUFFER_SIZE)
	{
		line = freejoin(line, buffer, -10);
		r = read(fd, buffer, BUFFER_SIZE);
		ft_bzero(&buffer[r], ft_strlen(&buffer[r]));
		if (fd < 0 || r < 0)
			free (line);
		if (fd < 0 || r < 0)
			return (NULL);
	}
	if (r == 0 && line[0])
		return (line);
	else if (r == 0)
	{
		free (line);
		return (NULL);
	}
	line = freejoin(line, buffer, 1);
	return (line);
}
