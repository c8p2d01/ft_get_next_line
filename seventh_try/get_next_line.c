/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:42:33 by clems             #+#    #+#             */
/*   Updated: 2021/07/09 14:48:14 by clems            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// return the length of the given string;
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i])
		i++;
	return (i);
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

// allocate memory that consists only of '\0' bytes
char	*ft_calloc(size_t nmemb, size_t n)
{
	char	*dest;
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

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

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dst;

	len = ft_strlen((char *)src) + 1;
	dst = malloc((len) + 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

// concatenate two strings into one new string
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1, 1);
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{	
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{	
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
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

char	*wert(char **s)
{
	char	*res;
	char	*temp;
	int		rlen;

	rlen = 0;
	while ((*s)[rlen] && (*s)[rlen] != '\n')
		rlen++;
	res = ft_calloc(rlen + 2, sizeof(char));
	temp = ft_calloc(ft_strlen(ft_strchr(*s, '\n')) + 1, sizeof(char));
	if (!res || !temp)
		return (NULL);
	ft_memcpy(res, *s, rlen);
	res[rlen] = '\n';
	res[rlen + 1] = '\0';
	ft_memcpy(temp, &((*s)[rlen + 1]), ft_strlen(ft_strchr(*s, '\n')));
	free (*s);
	*s = ft_strdup(temp);
	free (temp);
	return (res);
}

char *get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*s;
	char		*tmp;
	int			r;

	r = BUFFER_SIZE;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		if (r < 0 || fd < 0)
			return (NULL);
		if (s == NULL)
			s = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(s, buffer);
			free (s);
			s = ft_strdup(tmp);
			free (tmp);
		}
		if (ft_strchr(s, '\n'))
			break ;
	}
	return (wert(&s));
}

