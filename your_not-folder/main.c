#include "../include/shell.h"

void	shell_expansion(t_shell *sh)
{
	char	*line;

	while (1)
	{
		gnl_v2(&line);
		g_gl.line = line;
		g_gl.numpipes = 0;
		parse_shell(sh, line, 0);
		sh->args_of_shell = ft_split_free(sh->args_of_shell);
		init_shell_struct(sh);
		free(line);
	}
}

void	init_shell_struct(t_shell *sh)
{
	sh->flag1 = 0;
	sh->flag2 = 0;
	sh->flagar = 0;
	sh->lenght = 0;
	sh->dollen = 0;
	sh->numargs = 0;
	sh->evkey = NULL;
	sh->evvalue = NULL;
	sh->valuelen = 0;
	sh->args_of_shell = NULL;
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	sh;

	write(1, "\033[1;36m\033[2m", ft_strlen("\033[1;32m\033[2m"));
	if (argc != 1)
	{
		print_error("hmm .. I think there're a lot of args.\n", 0);
		return (127);
	}
	argv = NULL;
	ft_bzero(&g_gl.root, sizeof(t_global));
	init_env(&g_gl.root, envp);
	signals();
	init_shell_struct(&sh);
	shell_expansion(&sh);
	return (0);
}

//	0123456789|123456789|12345678
	// echo "--$PWD--"'==$PWD=='
	// echo "--$PWD--'==$PWD=='--"
	// echo '--$PWD--"==$PWD=="--'
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

//echo '\'    $HOME===='"$HOME"; echo hi
//\ /Users/kstout===="$HOME"; echo hi

//echo "\"    $HOME===="'$HOME'; echo hi
//"    /Users/kstout====$HOME
//hi

//echo '"$HOME"; echo hi
//"$HOME"; echo hi

//echo '"$HOME"'; echo hi
//"$HOME"
//hi

//echo "'$HOME'
//'/Users/kstout'
