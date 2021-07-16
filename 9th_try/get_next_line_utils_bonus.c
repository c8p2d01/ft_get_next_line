/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:42:33 by clems             #+#    #+#             */
/*   Updated: 2021/07/09 14:48:14 by clems            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

// allocate memory that consists only of '\0' bytes
char	*ft_calloc(size_t nmemb, size_t n)
{
	char	*dest;
	size_t	i;

	dest = malloc(nmemb * n);
	if (!dest)
		return (0);
	i = 0;
	while (i < n * nmemb)
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
char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	*f;

	f = (unsigned char *)str;
	i = 0;
	while (f[i])
	{
		if (f[i] == c)
			return ((char *)(f + i));
		i++;
	}
	if (f[i] == c)
		return ((char *)(f + i));
	return (NULL);
}
