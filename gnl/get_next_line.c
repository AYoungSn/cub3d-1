#include "get_next_line.h"

char	*ft_substr(char *str, int start, int len)
{
	char	*result;

	if (!str || !(result = malloc(sizeof(char) * len + 1)))
		return (0);
	if (start >= ft_strlen(str))
	{
		*result = 0;
		return (result);
	}
	ft_strlcpy(result, str + start, len + 1);
	return (result);
}

int		save_line(char **dest, char *src, char **save)
{
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp = *dest;
	len = ft_findchar(src);
	if (src[len] == '\n')
	{
		tmp2 = ft_substr(src, 0, len);
		*dest = ft_strjoin(*dest, tmp2);
		if (src[len + 1] != '\0')
			*save = ft_substr(src, len + 1, ft_strlen(src) - len - 1);
		free(tmp);
		free(tmp2);
		return (1);
	}
	*dest = ft_strjoin(*dest, src);
	free(tmp);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*back[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			nread;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_substr("", 0, 0);
	if (back[fd])
	{
		tmp = back[fd];
		nread = save_line(line, back[fd], &back[fd]);
		free(tmp);
		if (tmp == back[fd])
			back[fd] = 0;
		if (nread)
			return (1);
	}
	while ((nread = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[nread] = 0;
		if (save_line(line, buf, &back[fd]) > 0)
			return (1);
	}
	return (nread > 0 ? 1 : nread);
}
