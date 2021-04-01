#include "../include/mine.h"

void shell_expansion(t_shell *sh)
{
	char	*line;

	while (1)
	{
//		get_next_line(0, &line);
		gnl_v2(&line);
		parse_shell(sh, line, 0);
		free(sh->args_of_shell);
		init_shell_struct(sh);
		free(line);
	}
}

void init_shell_struct(t_shell *sh)
{
	sh->flag1 = 0;
	sh->flag2 = 0;
	sh->lenght = 0;
	sh->dollen = 0;
	sh->numargs = 0;
	sh->evkey = NULL;
	sh->evvalue = NULL;
	sh->valuelen = 0;
	sh->args_of_shell = NULL;
}

int main(int argc, char *argv[], char **envp)
{
	ft_bzero(&g.root, sizeof(t_global));
	init_env(&g.root, envp);
	g.argv = argv;
	if (!argc)
		return (-1);
//	t_list *next = g.root;
//	printf("ok, write smth below:\n");
	t_shell sh;
	init_shell_struct(&sh);
	shell_expansion(&sh);

	delete_list(&g.root);
	return (0);
}

//	0123456789|123456789|12345678
//	echo "--$PWD--"'==$PWD=='
//	echo "--$PWD--'==$PWD=='--"
//	echo '--$PWD--"==$PWD=="--'
//	0123456789|123456789|12345678

//	echo "--$HOME--"'==$HOME=='
//	--/home/kstout--==$HOME==

//	echo "--$HOME--$HOME--"'==$HOME==$HOME=='
//	--/home/kstout--/home/kstout--==$HOME==$HOME==

//	echo "--$HOME--'==$HOME=='--"
//	--/home/kstout--'==/home/kstout=='--

//	echo "--$HOME--$HOME--'==$HOME==$HOME=='--"
//	--/home/kstout--/home/kstout--'==/home/kstout==/home/kstout=='--

//	echo '--$HOME--"==$HOME=="--'
//	--$HOME--"==$HOME=="--

//	echo '--$HOME--$HOME--"==$HOME==$HOME=="--'
//	--$HOME--$HOME--"==$HOME==$HOME=="--

//	echo --$HOME--==$HOME==--
//	--/home/kstout--==/home/kstout==--

//	echo --$HOME--         ==$HOME==--
//	--/home/kstout-- ==/home/kstout==--

//	echo '--$HOME--         ==$HOME==--'
//	--$HOME--         ==$HOME==--

//	echo "--$HOME--         ==$HOME==--"
//	--/home/kstout--         ==/home/kstout==--
