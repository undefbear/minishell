#include "../include/shell.h"

char 	**ft_realloc(char **strs, char *value)
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

void	redir_func_2(int fd_r, int fd_l, char **cmd)
{
	pid_t	pid;
	int		n;

	pid = fork();
	if (!pid)
	{
		if (fd_r > 0)
			dup2(fd_r, 1);
		if (fd_l > 0)
			dup2(fd_l, 0);
		if (g_gl.numpipes)
			its_last_pipe(cmd);
		else
			commands(cmd);
		exit(ft_atoi(g_gl.error_code));
	}
	waitpid(pid, &n, 0);
	arg_itoa(n);
	if (fd_r != -2)
		close(fd_r);
	if (fd_l != -2)
		close(fd_l);
	free(cmd);
}

void	redir_func(char **cmd, char *nameright, char *nameleft, int f)
{
	int		fd_r;
	int		fd_l;

	fd_r = -2;
	fd_l = -2;
	if (nameright)
	{
		if (f)
			fd_r = open(nameright, O_RDWR | O_TRUNC);
		else
			fd_r = open(nameright, O_RDWR | O_APPEND);
	}
	if (nameleft)
		fd_l = open(nameleft, O_RDONLY);
	if (arr_size(cmd) >= 1)
		redir_func_2(fd_r, fd_l, cmd);
}

char	*read_file(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (name);
	}
	write(2, "minishell:  No such file or directory\n", 37);
	return (NULL);
}
