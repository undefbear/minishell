#include "../include/shell.h"
//       filedes[0] предназначен для чтения, а filedes[1] предназначен для записи.

static int  check_redir(char **args)
{
    int i;

    i = -1;
    while(args[++i])
    {
        if (equals(args[i], ">") || equals(args[i], "<") || equals(args[i], ">>"))
            return (0);
    }
    return (1);
}

static void check_redir_bred(t_shell *sh) {
    char **res;
    int size;
    int i;

    i = -1;
    size = 0;
    while (sh->args_of_shell[++i])
        if (equals(sh->args_of_shell[i], "<")
            || equals(sh->args_of_shell[i], ">") || equals(sh->args_of_shell[i], ">>"))
            size++;
    res = malloc(sizeof(char *) * (arr_size(sh->args_of_shell) - size + 1));
    i = -1;
    size = 0;
    while (sh->args_of_shell[++i]) {
        if (!(equals(sh->args_of_shell[i], "<")
              || equals(sh->args_of_shell[i], ">") || equals(sh->args_of_shell[i], ">>")))
            res[i - size] = ft_strdup(sh->args_of_shell[i]);
        else
            size++;
    }
    res[i - size] = NULL;
    ft_split_free(sh->args_of_shell);
    sh->args_of_shell = res;
}

int	its_pipe(t_shell *sh, int f)
{
	pipe(g_gl.fdp);
	pid_t pid = fork();
	if (!pid && !f)
	{
		close(g_gl.fdp[0]);
		dup2(g_gl.fdp[1], 1);
		if (check_redir(sh->args_of_shell))
		    commands(sh->args_of_shell);
        exit(0);
	}
	else if (!pid)
	{
		close(g_gl.fdp[0]);
		dup2(g_gl.fdp[1], 1);
		close(g_gl.fd_in);
		dup2(g_gl.fd_out, 0);
        check_redir_bred(sh);
        commands(sh->args_of_shell);
        exit(0);
	}
	close(g_gl.fdp[1]);
    if (f)
		close(g_gl.fd_out);
	g_gl.fd_out = g_gl.fdp[0];
	g_gl.fd_in = g_gl.fdp[1];
	return (0);
}

int	its_last_pipe(char **sh)
{
	int a;

	pid_t pid = fork();
	if (!pid)
	{
		close(g_gl.fd_in);
		dup2(g_gl.fd_out, 0);
        commands(sh);
		exit(atoi(g_gl.error_code));
	}
	close(g_gl.fd_out);
	close(g_gl.fdp[1]);
	waitpid(pid, &a, 0);
    arg_itoa(a);
	g_gl.fd_out = 1;
	g_gl.fd_in = 0;
	return (0);
}

// env | grep TERM | grep LC
// env > a >> c | grep TERM < c | wc -l >> c; echo TERM12345 >> c | grep TERM > y