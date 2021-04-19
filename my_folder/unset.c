#include "../include/shell.h"

int	is_str_valid_my(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!(!ft_isalpha(str[i]) || str[i] != '_'))
				return (0);
		}
		else
			if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
				return (0);
	}
	return (1);
}

void	cmd_unset(char **cmd)
{
	int	i;

	i = 0;
	if (arr_size(cmd) == 1)
		return ;
	while (cmd[++i])
	{
		if (ft_strlen(cmd[i]) == 1 && cmd[i][0] == '_')
			continue ;
		if (is_str_valid_my(cmd[i]))
		{
			remove_elem(&g_gl.root, cmd[i]);
			remove_elem(&g_gl.export, cmd[i]);
		}
		else
		{
			g_gl.error_code[0] = '1';
			g_gl.error_code[1] = 0;
			print_error("minishell:  unset: `", 0);
			print_error(cmd[i], 0);
			print_error("': not a valid identifier", 1);
		}
	}
}
