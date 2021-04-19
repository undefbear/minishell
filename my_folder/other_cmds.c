#include "../include/shell.h"

char	*cheack_path_2(char *cmd, char *path)
{
	char	*name;
	char	*file;
	int		fd;

	name = finde_new_path(&path);
	while (name)
	{
		file = ft_strjoin(name, cmd);
		fd = open(file, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			free(path);
			free(name);
			return (file);
		}
		free(name);
		free(file);
		name = finde_new_path(&path);
	}
	free(path);
	free(name);
	return (NULL);
}

static void	write_error(void)
{
	if (g_gl.error_code[0] == '0')
	{
		g_gl.error_code[0] = '1';
		g_gl.error_code[1] = 0;
	}
}

static void	other_cmd_without_slesh_2(char **cmd, char **env, char *cmd_name)
{
	char	*n_cmd;
	int		rv;

	n_cmd = cheack_path(cmd[0]);
	if (n_cmd)
	{
		g_gl.pid = fork();
		if (g_gl.pid == 0)
			exit(execve(n_cmd, cmd, env));
		else
			waitpid(g_gl.pid, &rv, 0);
		if (rv)
			write_error();
		free(n_cmd);
	}
	else
	{
		err_code127();
		print_error("minishell:  ", 0);
		print_error(cmd_name, 0);
		print_error(": command not found\n", 0);
	}	
}

void	other_cmd_without_slesh(char **cmd)
{
	char	**env;
	char	*cmd_name;

	if (!cmd[0][0])
	{
		err_code127();
		print_error("minishell:  : command not found\n", 0);
		return ;
	}
	cmd_name = cmd[0];
	env = env_to_args();
	other_cmd_without_slesh_2(cmd, env, cmd_name);
	ft_split_free(env);
	g_gl.pid = 0;
}
