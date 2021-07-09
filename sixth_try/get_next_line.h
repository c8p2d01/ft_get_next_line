/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:07:59 by clems             #+#    #+#             */
/*   Updated: 2021/07/09 14:52:43 by clems            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

size_t	ft_strlen(char *s);

size_t	ft_sublen(char *s);

void	*ft_calloc(size_t nmemb, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	ft_memmove(void *dest, const void *src, size_t n);

char	*ft_strchr(const char *s, int c);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_getjoin(char **s1, char const *s2);

int		get_next_line(int fd, char **line);

#endif