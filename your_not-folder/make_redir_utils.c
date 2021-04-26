#include "../include/shell.h"

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
	if (fd_l > 0)
		g_gl.fd_out = fd_l;
	waitpid(pid, &n, 0);
	arg_itoa(n);
	if (fd_r != -2)
		close(fd_r);
	if (fd_l != -2)
		close(fd_l);
	free(cmd);
}

static void	print_error_dir(char *tmp, int f)
{
	err_code1();
	if (f)
	{
		print_error("minishell:  ", 0);
		print_error(tmp, 0);
		print_error(": Is a directory\n:  ", 0);
	}
	else
	{
		print_error("minishell:  ", 0);
		print_error(tmp, 0);
		print_error(": Permission denied\n:  ", 0);
	}
}

static int	redir_func_check(char *right, char *nameleft, int fd_r, int fd_l)
{
	char	*tmp;

	if ((right && fd_r < 0) || (nameleft && fd_l < 0))
	{
		if (right)
			tmp = right;
		else
			tmp = nameleft;
		if (opendir(tmp))
			print_error_dir(tmp, 1);
		else
			print_error_dir(tmp, 0);
		return (1);
	}
	return (0);
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
	if (redir_func_check(nameright, nameleft, fd_r, fd_r))
		return ;
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
