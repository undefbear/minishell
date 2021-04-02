#include "../include/mine.h"

void create_env(t_shell *sh, int *z, int *i)
{
	int k;

	k = 0;
	*i += sh->dollen;
	sh->lenght = sh->lenght - sh->dollen;
	while (sh->valuelen-- != 0)
		sh->args_of_shell[sh->numargs][(*z)++] = sh->evvalue[k++];
	sh->dollen = 0;
	free(sh->evkey);
	sh->evkey = NULL;
	sh->valuelen = 0;
}

void create_word(t_shell *sh, char *line, int *i, int *z)
{
	//todo проверка на '\' 92
//	if (line[*i] == 92)
//		(*i)++;

	if ((line[*i] == '\t' || line[*i] == '\n' || line[*i] == '\r'
		 || line[*i] == '\v' || line[*i] == '\f') &&
		(sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0))
		line[*i] = ' ';
	else
		sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)++];
}

int its_env_var(char c)
{
	if ((c != '\0' && c != ' ') &&
	((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		return (0);
	else
		return (1);
}

void change_pos(t_shell *sh, char c, int *i)
{
	if (c == 32)
	{
		sh->numargs++;
		init_new_pointer(sh);
	}
	else if (c == 59) //;
	{
		(*i)++;
		commands(sh->args_of_shell);
		int z = 0;
		while (z <= sh->numargs + 1)
		{
			printf("aos[%d] |%s|\n", z, sh->args_of_shell[z]);
			z++;
		}
		printf("---------------------------------------------\n");
		free(sh->args_of_shell);
		init_shell_struct(sh);
		init_first_pointer(sh);
	}
}