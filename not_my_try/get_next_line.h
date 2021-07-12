#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define FD_SIZE 4096
# include <stdlib.h>
# include <unistd.h>

int		get_next_line_old(int fd, char **line);
char    *get_next_line(int fd);
int		retvalcalc(char **s, char **line, int ret, int fd);
int		writeline(char **s, char **line);
void	ft_strdel(char **as);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
