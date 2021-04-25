#include "../include/shell.h"

static char	**check_bred(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = -1;
	j = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '=')
			break ;
		if (!ft_strchr(cmd[i], '='))
			break ;
	}
	new_cmd = malloc(sizeof(char *) * (arr_size(cmd) - i + 1));
	if (!new_cmd)
		cmd_exit(NULL);
	ft_bzero(new_cmd, sizeof(char *) * (arr_size(cmd) - i + 1));
	while (cmd[++j + i])
		new_cmd[j] = ft_strdup(cmd[j + i]);
	new_cmd[j] = NULL;
	return (new_cmd);
}

static void	commands2(char **new_cmd)
{
	if (equals(PWD, new_cmd[0]))
		cmd_pwd();
	else if (equals(CD, new_cmd[0]))
		cmd_cd(new_cmd);
	else if (equals(EXPORT, new_cmd[0]))
		cmd_export(new_cmd);
	else if (equals(ENV, new_cmd[0]))
		cmd_env(new_cmd);
	else if (equals(UNSET, new_cmd[0]))
		cmd_unset(new_cmd);
	else if (equals(_ECHO, new_cmd[0]))
		cmd_echo(new_cmd);
	else if (equals(EXIT, new_cmd[0]))
		cmd_exit(new_cmd);
	else if (equals(AUTH, new_cmd[0]))
		cmd_auth();
	else
		other_cmd(new_cmd);
}

void	commands(char **cmd)
{
	char	**new_cmd;

	if (arr_size(cmd))
	{
		g_gl.error_code[0] = '0';
		g_gl.error_code[1] = 0;
		new_cmd = check_bred(cmd);
		g_gl.cmd = new_cmd[0];
		commands2(new_cmd);
		ft_split_free(new_cmd);
	}
	else if (g_gl.flag_semi)
	{
		err_code258();
		g_gl.flag_semi = 0;
		print_error("minishell:  syntax error near unexpected token `;'", 1);
	}
}
