#include "../include/shell.h"

void	cmd_echo_n(char **cmd)
{
	int	i;
	int	f;

	f = 0;
	g_gl.echon = arr_size(cmd) - 3;
	i = 0;
	while (cmd[++i])
	{
		if (!equals(cmd[i], "-n") || f)
		{
			f = 1;
			g_gl.echon += ft_strlen(cmd[i]);
			if (cmd[i + 1])
			{
				write(1, cmd[i], ft_strlen(cmd[i]));
				write(1, " ", 1);
			}
			else
				write(1, cmd[i], ft_strlen(cmd[i]));
		}
	}
}

void	cmd_echo_not_n(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i + 1])
			printf("%s ", cmd[i]);
		else
			printf("%s\n", cmd[i]);
	}
}

void	cmd_echo(char **cmd)
{
	if (arr_size(cmd) == 1)
		printf("\n");
	else if (equals(cmd[1], "-n"))
		cmd_echo_n(cmd);
	else
		cmd_echo_not_n(cmd);
}
