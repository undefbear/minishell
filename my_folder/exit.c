#include "../include/shell.h"

static	void	free_all(void)
{
	ft_split_free(g_gl.sh.args_of_shell);
	free(g_gl.line);
	free(g_gl.sh.evkey);
	delete_list(&g_gl.root);
	delete_list(&g_gl.export);
	delete_hist(&g_gl.head, &g_gl.tail);
}

static int	check_param(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
				return (255);
		}
		else if (!ft_isdigit(str[i]) || ft_strlen(str) >= 20)
			return (255);
	}
	return (0);
}

static void	cmd_exit_2(char **cmd)
{
	if (!check_param(cmd[1]))
	{
		g_gl.error_code[0] = '1';
		g_gl.error_code[1] = 0;
		printf("exit\n");
		print_error("minishell:  exit: too many arguments\n", 0);
	}
	else
	{
		printf("exit\n");
		print_error("minishell:  exit: ", 0);
		print_error(cmd[1], 0);
		print_error(": numeric argument required\n", 0);
		free_all();
		exit(255);
	}
}

static void	cmd_exit_3(char **cmd)
{
	unsigned char	exit_code;

	exit_code = check_param(cmd[1]);
	if (exit_code)
	{
		printf("exit\n");
		print_error("minishell:  exit: ", 0);
		print_error(cmd[1], 0);
		print_error(": numeric argument required\n", 0);
		free_all();
		exit(exit_code);
	}
	exit_code = ft_atoi(cmd[1]);
	printf("exit\n");
	free_all();
	exit(exit_code);
}

void	cmd_exit(char **cmd)
{
	if (!cmd)
	{
		free_all();
		print_error("minishell:  jadniy malloc :,(\n", 0);
		exit(127);
	}
	if (arr_size(cmd) == 1)
	{
		if (g_gl.flag)
		{
			write(0, "exit\n", 5);
			free_all();
			exit(0);
		}
		free_all();
		printf("exit\n");
		exit(0);
	}
	else if (arr_size(cmd) > 2)
		cmd_exit_2(cmd);
	else
		cmd_exit_3(cmd);
}
