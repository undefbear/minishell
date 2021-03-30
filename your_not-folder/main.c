#include <stdio.h>
#include <stdlib.h>
#include "../include/mine.h"
#include "../include/shell.h"
#include "../include/get_next_line.h"

int shell_expansion(t_shell *sh)
{
	char	*line;

	while (1)
	{
		// get_next_line(0, &line);
		// gnl_v2(&line);
		parse_shell(sh, line, 0);
		init_aos(sh);
		free(line);
	}
	return (0);
}

void init_aos(t_shell *sh)
{
	sh->flag1 = 0;
	sh->flag2 = 0;
	sh->lenght = 0;
	sh->dollen = 0;
	sh->numargs = 0;
//	sh->i = 0;
//	sh->dkey[15];
	sh->dvalue = NULL;
	sh->args_of_shell = NULL;
}

int main(int argc, char *argv[], char **envp)
{
	ft_bzero(&g.root, sizeof(t_global));
	// signals();
	init_env(&g.root, envp);
	g.argv = argv;
	if (!argc)
		return (-1);
//	t_list *next = g.root;
	printf("ok, write smth below:\n");
//	echo "--$TERM--"'--$TERM--'
//	echo "--$TERM--'==$TERM=='--"
//	echo '--$TERM--"==$TERM=="--'
//	0123456789|123456789|12345689
	t_shell sh;
	init_aos(&sh);
	shell_expansion(&sh);
	printf("----------------------------------\n");
	free(&sh);
	delete_list(&g.root);
	return (0);
}

