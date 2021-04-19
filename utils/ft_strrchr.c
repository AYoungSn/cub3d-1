#include "utils.h"

char	*ft_strrchr(char *s, int c)
{
	int	size;

	size = ft_strlen(s) + 1;
	while (size--)
	{
		if (s[size] == (char)c)
			return ((char*)(s + size));
	}
	return (NULL);
}
