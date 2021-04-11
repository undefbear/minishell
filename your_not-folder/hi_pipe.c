#include "../include/shell.h"
//       filedes[0] предназначен для чтения, а filedes[1] предназначен для записи.

int	its_pipe(t_shell *sh, int f)
{
	int a;

	pipe(g.fdp);
	pid_t pid = fork();
	if (!pid && !f)
	{
		close(g.fdp[0]);
		dup2(g.fdp[1], 1);
		commands(sh->args_of_shell);
		exit(0);
	}
	else if (!pid)
	{
		close(g.fdp[0]);
		dup2(g.fdp[1], 1);
		close(g.fd_in);
		dup2(g.fd_out, 0);
		commands(sh->args_of_shell);
		exit(0);
	}
	close(g.fdp[1]);
	if (f)
		close(g.fd_out);
	waitpid(pid, &a, 0);
	g.fd_out = g.fdp[0];
	g.fd_in = g.fdp[1];
	return (0);
}
int	its_last_pipe(char **sh)
{
	int a;

	pid_t pid = fork();
	if (!pid)
	{
		close(g.fd_in);
		dup2(g.fd_out, 0);
		commands(sh);
		exit(0);
	}
	close(g.fd_out);
	close(g.fdp[1]);
	waitpid(pid, &a, 0);
	g.fd_out = 1;
	g.fd_in = 0;
	return (0);
}

// env | grep TERM | grep LC