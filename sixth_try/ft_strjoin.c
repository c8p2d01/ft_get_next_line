/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:58:42 by clems             #+#    #+#             */
/*   Updated: 2021/05/27 12:28:05 by clems            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// concatenate two strings into one new string
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_length;
	size_t	length_dst;
	size_t	length_src;
	char	*res;

	length_dst = ft_strlen((char *)s1);
	length_src = ft_strlen((char *)s2);
	total_length = length_src + length_dst;
	res = malloc(total_length + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, length_dst + 1);
	ft_strlcpy(&res[(length_dst)], s2, length_src + 1);
	return (res);
}
//#include <stdio.h>
//int main()
//{
//	char	strang[] = "Zer";
//	char	strung[] = "schmetterling";
//	printf("%s\n%s\n%s\n", strang, strung, ft_strjoin(strang, strung));
//}
