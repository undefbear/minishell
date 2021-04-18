#include "../include/shell.h"

char 	**ft_realloc(char **strs, char *value)
{
	int i;
	char **res;

	if (!strs)
	{
		res = malloc(sizeof(char*) *(2));
		res[0] = value;
		res[1] = NULL;
		return (res);
	}
	i = 0;
	while(strs[i])
		i++;
	res = malloc(sizeof(char*) *(i + 2));
	i = -1;
	while(strs[++i])
		res[i] = strs[i];
	res[i] = value;
	res[i + 1] = NULL;
	free(strs);
	return res;
}

char	*create_file(char *name, int f)
{
	int fd;

	if (f)
		fd = open(name, O_TRUNC | O_RDWR | O_CREAT, S_IRWXU);
	else
		fd = open(name,  O_APPEND | O_RDWR | O_CREAT, S_IRWXU);
	close(fd);
	return (name);
}

void	redir_func(char **cmd, char *nameright, char *nameleft, int f)
{
	int fd_r;
	int fd_l;
	int n;

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
    {
        pid_t pid = fork();
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
            exit(0);
        }
        else
        {
            waitpid(pid, &n, 0);
            if (fd_r != -2)
                close(fd_r);
            if (fd_l != -2)
                close(fd_l);
            free(cmd);
        }
    }
}

char	*read_file(char *name)
{
	int fd;

	if ((fd = open(name, O_RDONLY)) != -1)
	{
		close(fd);
		return (name);
	}
	write(2, "minishell:  No such file or directory\n", 37);
	return (NULL);
}

void make_redirection(char **aos)
{
	int z = -1;
	char *nameright;
	char *nameleft;
	char **res;
	int f;

	nameleft = NULL;
	nameright = NULL;
	res = NULL;
	while (aos[++z])
	{
		if (!z && !equals(aos[z], ">") && !equals(aos[z], "<") && !equals(aos[z], ">>"))
			res = ft_realloc(res, aos[z]);
		else if (aos[z][0] == '>' && aos[z][1] == '>')
		{
			f = 0;
			if (aos[++z])
				nameright = create_file(aos[z], f);
			else
			{
				write(2, "minishell:  syntax error near unexpected token `newline'\n", 57);
				return ;
			}
		}
		else if (aos[z][0] == '>')
		{
			f = 1;
			if (aos[++z])
				nameright = create_file(aos[z], f);
			else
			{
				write(2, "minishell:  syntax error near unexpected token `newline'\n", 57);
				return ;
			}
		}
		else if (aos[z][0] == '<')
		{
			if (aos[++z])
			{
				if (!(nameleft = read_file(aos[z])))
					return ;
			}
			else
			{
				write(2, "minishell:  syntax error near unexpected token `newline'\n", 57);
				return ;
			}
		}
		else
			res = ft_realloc(res, aos[z]);
	}
	redir_func(res, nameright, nameleft, f);
	g_gl.sh.flagar = 0;
}
