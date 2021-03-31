#ifndef MINISHELL_D_H
#define MINISHELL_D_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/shell.h"
#include "../include/get_next_line.h"
#include <wait.h>

typedef struct s_shell
{
	int flag1;
	int flag2;
	int lenght;
	int dollen;
	int numargs;
	char *evkey;
	char *evvalue;
	int valuelen;
	char **args_of_shell;
}				t_shell;

int parse_shell(t_shell *sh, char *line, int i);
void if_find_elem(char *arg, int *i, t_shell *sh);
int prepare_array(t_shell *sh, char *arg, int *i, char till);
void init_shell_struct(t_shell *sh);
int init_env_var(char *dollar, t_shell *sh);
int find_lenght(char *line, char till, int i);
int find_value(t_shell *sh);
char *init_array(t_shell *sh, int linelen);
int create_words(t_shell *sh, char *line, int *i);
int correct_env_var(char c);
int create_tokens (t_shell *sh, char *line, int *i, int linelen);
//int create_env(t_shell *sh, int *z, int *k, int linelen);

#endif //MINISHELL_D_H
