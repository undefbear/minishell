#include "../include/shell.h"

static int	sintax_error(int *f, char **aos, int *z, char **name)
{
	if (aos[++(*z)] && !equals(aos[(*z)], ">")
		&& !equals(aos[(*z)], "<") && !equals(aos[(*z)], ">>"))
		*name = create_file(aos[*z], *f);
	else
	{
		write(2, "minishell:  syntax error near unexpected token `newline'\n",
			57);
		g_gl.error_code[0] = '2';
		g_gl.error_code[1] = '5';
		g_gl.error_code[2] = '8';
		g_gl.error_code[3] = 0;
		return (1);
	}
	return (0);
}

static int	make_redirection_while_2(char **aos, int *f, char ***res, int *z)
{
	if (aos[*z][0] == '>')
	{
		*f = 1;
		if (sintax_error(f, aos, z, &g_gl.nameright))
			return (1);
	}
	else if (aos[*z][0] == '<')
	{
		*f = 0;
		if (sintax_error(f, aos, z, &g_gl.nameleft))
			return (1);
	}
	else
		*res = ft_realloc(*res, aos[*z]);
	return (0);
}

static int	make_redirection_while(char **aos, int *f, char ***res, int *z)
{
	while (aos[++(*z)])
	{
		if (!(*z) && !equals(aos[*z], ">")
			&& !equals(aos[*z], "<") && !equals(aos[*z], ">>"))
			*res = ft_realloc(*res, aos[*z]);
		else if (aos[*z][0] == '>' && aos[*z][1] == '>')
		{
			*f = 0;
			if (sintax_error(f, aos, z, &g_gl.nameright))
				return (1);
		}
		else if (make_redirection_while_2(aos, f, res, z))
			return (1);
	}
	return (0);
}

void	make_redirection(char **aos)
{
	int		z;
	char	**res;
	int		f;

	z = -1;
	g_gl.nameleft = NULL;
	g_gl.nameright = NULL;
	res = NULL;
	if (make_redirection_while(aos, &f, &res, &z))
		return ;
	redir_func(res, g_gl.nameright, g_gl.nameleft, f);
	g_gl.sh.flagar = 0;
}
