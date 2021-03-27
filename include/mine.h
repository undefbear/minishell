//
// Created by kstout on 3/26/21.
//

#ifndef MINISHELL_D_H
#define MINISHELL_D_H

typedef struct s_shell
{
	int flag1;
	int flag2;
	int lenght;
	int dollen;
	int numargs;
	char dkey[15];
	char *dvalue;
	char **args_of_shell;
}				t_shell;

int parse_shell(t_shell *sh, char *line, int i);
void if_find_elem(char *arg, int *i, t_shell *sh);
int write_args(t_shell *sh, char *arg, int *i, char till);
void init_aos(t_shell *sh);

#endif //MINISHELL_D_H
