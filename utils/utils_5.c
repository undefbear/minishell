#include "../include/shell.h"

char	**ft_realloc(char **strs, char *value)
{
	int		i;
	char	**res;

	if (!strs)
	{
		res = malloc(sizeof(char *) * (2));
		if (!res)
			cmd_exit(NULL);
		res[0] = value;
		res[1] = NULL;
		return (res);
	}
	i = 0;
	while (strs[i])
		i++;
	res = malloc(sizeof(char *) *(i + 2));
	if (!res)
		cmd_exit(NULL);
	i = -1;
	while (strs[++i])
		res[i] = strs[i];
	res[i] = value;
	res[i + 1] = NULL;
	free(strs);
	return (res);
}

char	*create_file(char *name, int f)
{
	int	fd;

	if (f)
		fd = open(name, O_TRUNC | O_RDWR | O_CREAT, S_IRWXU);
	else
		fd = open(name, O_APPEND | O_RDWR | O_CREAT, S_IRWXU);
	close(fd);
	return (name);
}

int	is_sym_valid(int c)
{
	if (c >= 48 && c <= 57)
		return (0000000);
	else if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (0);
	else if (c == '/' || c == ':' || c == '_' || c == '.'
		|| c == ';' || c == '=' || c == ' ')
		return (0);
	return (1);
}
