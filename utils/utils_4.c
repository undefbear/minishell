#include "../include/shell.h"

void	*ft_split_free(char **start)
{
	int	i;

	i = 0;
	while (start && start[i] != NULL)
		free(start[i++]);
	free(start);
	return (NULL);
}

void	put_srt(char *str)
{
	write(1, str, ft_strlen(str));
}

void	put_srtln(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	tmp_h;
	int	i;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	tmp_h = 0;
	while (haystack[tmp_h] && tmp_h < len)
	{
		if (haystack[tmp_h] == needle[0])
		{
			i = 1;
			while (needle[i] && haystack[tmp_h + i] == needle[i]
				   && (tmp_h + i) < len)
				i++;
			if (needle[i] == '\0')
				return ((char *)haystack + tmp_h);
		}
		tmp_h++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	sb;

	sb = (char)c;
	while (*s)
	{
		if (*s == sb)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}
