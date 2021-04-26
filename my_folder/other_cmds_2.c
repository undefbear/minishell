#include "../include/shell.h"

void	arg_itoa(int rv)
{
	char	res[10];
	int		i;
	int		j;
	int		num;

	num = WEXITSTATUS(rv);
	i = 0;
	j = 0;
	if (num)
	{
		while (num)
		{
			res[i++] = num % 10 + '0';
			num = num / 10;
		}
		while (j < i)
		{
			g_gl.error_code[j] = res[i - j - 1];
			j++;
		}
		return ;
	}
	g_gl.error_code[0] = '0';
	g_gl.error_code[1] = '\0';
}

char	*cheack_path(char *cmd)
{
	char	*path;

	path = ft_strdup(find_list(g_gl.root, "PATH"));
	if (path)
		return (cheack_path_2(cmd, path));
	return (NULL);
}

int	check_slesh(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 1 && str[0] == '/')
		return (1);
	if (len > 2 && (str[0] == '.' && str[1] == '/'))
		return (1);
	if (len > 3 && (str[0] == '.' && str[1] == '.' && str[2] == '/'))
		return (1);
	return (0);
}
