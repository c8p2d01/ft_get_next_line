/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clems <clems@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 BUFFER_SIZE:18:06 by clems             #+#    #+#             */
/*   Updated: 2021/06/03 13:08:46 by clems            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int	fd = open("test", O_RDONLY);
	char	*str;
	char	*str2;
	str = calloc(BUFFER_SIZE, 1);
	str2 = calloc(BUFFER_SIZE, 1);
	read(fd, str, BUFFER_SIZE);
	read(fd, str2, BUFFER_SIZE);
	write(1, str, BUFFER_SIZE);
	write(1, str2, BUFFER_SIZE);
	write(1, "\n", 1);
	close(fd);
}