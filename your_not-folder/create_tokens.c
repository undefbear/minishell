#include "../include/mine.h"

int check_double(t_shell *sh, char *line, int *i, int *z)
{
	if (sh->flag1 % 2 == 0) //не в других кавычках
	{
		if (sh->flag2 % 2 == 0)
			return (-1); //выход для смены аргумента
		else
		{
			(*i)++;
			sh->flag2++;
			return (1); //переходит на след элемент
		}
	}
	else
	{
		sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)];
		return (-1); //выход для смены аргумента
	}
}

int check_single(t_shell *sh, char *line, int *i, int *z)
{
	if (sh->flag2 % 2 == 0)
	{
		if (sh->flag1 % 2 == 0)
			return (-1); //выход для смены аргумента
		else
		{
			(*i)++;
			sh->flag1++;
			return (1); //переходит на след элемент
		}
	}
	else
	{
		sh->args_of_shell[sh->numargs][(*z)++] = line[(*i)];
		return (-1); //выход для смены аргумента
	}
}

int check_elem(t_shell *sh, char *line, int *i, int *z)
{
	if (line[*i] == 34) //"
		return(check_double(sh, line, i, z));
	else if (line[*i] == 39) //'
		return(check_single(sh, line, i, z));
	else if ((line[*i] == 32 && sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0)
			|| (line[*i] == 36 && !sh->dollen) || (line[*i] == 59))
	{
		sh->dollen = 0;
		return (-1); //выход для смены аргумента
	}
	else if (line[(*i)] == 36 && sh->dollen > 0)
		create_env(sh, z, i);
	return (0);
}

//запись токенов в массив
int create_tokens (t_shell *sh, char *line, int *i)
{
	int z;
	int res;

	z = 0;
	res = 0;
	while (sh->lenght-- > 0 && line[(*i)] != '\0')
	{
		res = check_elem(sh, line, i, &z);
		if (res == 1)
			break;
		else if (res == -1)
		{
			sh->args_of_shell[sh->numargs][z] = '\0';
			return (0);
		}
		else
			create_word(sh, line, i, &z);
	}
	sh->args_of_shell[sh->numargs][z] = '\0';
	return (0);
}