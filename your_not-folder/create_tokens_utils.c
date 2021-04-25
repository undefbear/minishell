#include "../include/shell.h"

//запись перемнной окружения в массив
void	create_env(t_shell *sh, int *z, int *i)
{
	int	k;

	k = 0;
	if (sh->dollen == -2)
		sh->dollen = 1;
	*i += sh->dollen;
	sh->lenght = sh->lenght - sh->dollen;
	while (sh->valuelen-- != 0)
		sh->args_of_shell[sh->numargs][(*z)++] = sh->evvalue[k++];
	sh->dollen = 0;
	free(sh->evkey);
	sh->evkey = NULL;
	sh->valuelen = 0;
}

//экранирование
int	escape_character(t_shell *sh, char *line, int *i, int *z)
{
	if (sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0)
	{
		if (line[(*i) + 1] == 36)
			sh->args_of_shell[sh->numargs][(*z)++] = line[++(*i)];
		(*i)++;
			if (line[(*i)] == 92)
				return (1);
		return (0);
	}
	else
	{
		if (line[(*i) + 1] == 36)
		{
			if (sh->flag2 % 2 != 0)
			{
				sh->args_of_shell[sh->numargs][(*z)++] = line[++(*i)];
				(*i)++;
				return (1);
			}
		}
		else
		{
			if (line[(*i) + 1] == 34 || line[(*i) + 1] == 39)
			{
				if (line[(*i) + 1] == 34 && sh->flag2 % 2 != 0)
				{
					sh->args_of_shell[sh->numargs][(*z)++] = line[++(*i)];
					(*i)++;
				} else if (line[(*i) + 1] == 39 && sh->flag1 % 2 != 0)
					sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)++];
				else
				{
					sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)++];
					sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)++];
				}
				return (1);
			}
		}
	}
	return (0);
}

//запись слова в массив
void	create_word(t_shell *sh, char *line, int *i, int *z)
{
	if (line[*i] == 92)
		if (escape_character(sh, line, i, z))
			return ;
	if ((line[*i] == '\t' || line[*i] == '\n' || line[*i] == '\r'
			|| line[*i] == '\v' || line[*i] == '\f')
		&& (sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0))
		line[*i] = ' ';
	else
		if ((line[*i] != '\0' && line[*i] != '$')
			|| (line[*i] == '$' && sh->flag2 % 2 == 0 && sh->flag1 % 2 != 0))
			sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)++];
}

//смена аргумента
void	change_pos(t_shell *sh, char c, int *i)
{
	if (c == 32 || c == 60 || c == 62)
	{
		if (c == 32 && sh->flag2 % 2 != 0)
			return;
		if (sh->args_of_shell[sh->numargs][0] == c)
			(*i)++;
		sh->numargs++;
		init_new_pointer(sh);
	}
	else if ((c == 59) || (c == 124))
	{
		if (sh->flagar == 2)
			its_pipe(sh, g_gl.numpipes);
		else if (sh->flagar == 1)
		{
			make_redirection(sh->args_of_shell);
		}
		if (c == 59 && !sh->flagar)
		{
			g_gl.flag_semi = 1;
			commands(sh->args_of_shell);
		}
		else if (c == 124)
		{
//			int z = 0; //todo print
//			while (z <= sh->numargs + 1)
//			{
//				printf("aos[%d] |%s|\n", z, sh->args_of_shell[z]);
//				z++;
//			}
//			printf("---------------------------------------------\n");
			its_pipe(sh, g_gl.numpipes);
			g_gl.numpipes = 1;
		}
		(*i)++;
		sh->args_of_shell = ft_split_free(sh->args_of_shell);
		if (c == 59)
			g_gl.numpipes = 0;
		init_shell_struct(sh);
		init_first_pointer(sh);
	}
}

int	init_first_pointer(t_shell *sh)
{
	sh->args_of_shell = malloc(sizeof(char *) * 2);
	if (!sh->args_of_shell)
		cmd_exit(NULL);
	sh->args_of_shell[0] = NULL;
	sh->args_of_shell[1] = NULL;
	return (0);
}
