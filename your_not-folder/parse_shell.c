#include <stdio.h>
#include <stdlib.h>
#include "../include/mine.h"
#include "../include/shell.h"
#include "../include/get_next_line.h"

//запись аргументов из строки в массив
int write_args(t_shell *sh, char *line, int *i, char till)
{
	int len;
	int valuelen;
	int z;
	int k;
	char *tmp;
	int tmplen;

	z = (*i);
	k = 0;
	len = 0;
	valuelen = 0;
	tmp = NULL;
	while (line[z] != '\0')
	{
		if (line[z] == till)
		{
			if (till != ' ')
				len += 2;
			break;
		}
		len++;
		z++;
	}
	z = 0;
	if (sh->dollen)
	{
		sh->dvalue = find_list(g.root, sh->dkey);
		//todo проверка нешел ли переменную
		if (sh->dvalue)
			valuelen = ft_strlen(sh->dvalue);
		else
			valuelen = 0;
	}
	if (sh->numargs !=0 && sh->args_of_shell[sh->numargs - 1][0] == 0)
		sh->numargs--;
	if (!sh->args_of_shell[sh->numargs])
	{
		if (!(sh->args_of_shell[sh->numargs] = malloc(
				sizeof(char *) * (len - sh->dollen + valuelen) + 1)))
			return (-1);
	}
	else
	{
		tmplen = ft_strlen(sh->args_of_shell[sh->numargs]);
		if (!(tmp = malloc(tmplen)))
			return (-1);
		tmp = sh->args_of_shell[sh->numargs];
		if (!(sh->args_of_shell[sh->numargs] = malloc(
				sizeof(char *) * (len - sh->dollen + valuelen) + 1)))
			return (-1);
	}
	while (len-- > 0)
	{
		if (line[(*i)] == 36 && sh->dollen)
		{
			*i += sh->dollen;
			len = len - sh->dollen;
			while (valuelen-- != 0)
				sh->args_of_shell[sh->numargs][z++] = sh->dvalue[k++];
		} else
			//todo проверка на "" '' $$
			if (line[*i] == 34)
			{
				if (sh->flag2 == 0 || sh->flag2 % 2 == 0)
					return (0);
				else
				{
					(*i)++;
					break;
				}
			}
			else if (line[*i] == 39)
			{
				if (sh->flag1 == 0 || sh->flag1 % 2 == 0)
					return (0);
				else
				{
					(*i)++;
					break;
				}
			}
			else if (line[*i] == 32 && sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0)
			{
				sh->dollen = 0;
				return (0);
			}
			else
			{
				if ((line[*i] == '\t' || line[*i] == '\n' || line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f') && (sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0))
				{
					line[*i] = ' ';
//					(*i)++;
				}
				else
						sh->args_of_shell[sh->numargs][z++] = line[(*i)++];
			}
	}
	sh->args_of_shell[sh->numargs][z] = '\0';
	if (tmp)
	{
		sh->args_of_shell[sh->numargs] = ft_strjoin(tmp, sh->args_of_shell[sh->numargs]);
		free(tmp);
	}
	if (sh->args_of_shell[sh->numargs][0] == 0)
	{
		free(sh->args_of_shell[sh->numargs]);
		sh->args_of_shell[sh->numargs] = NULL;
		sh->numargs--;
	}
	return (0);
}

//если найдены $ ' "
void if_find_elem(char *line, int *i, t_shell *sh)
{
	int k;
	char *dollar;
	k = 0;

	dollar = NULL;
	dollar = ft_strchr(&line[*i], 36);
	if (dollar)
	{
		dollar++;
		sh->dollen++;
		while (*dollar <= 90 && *dollar >= 65)
		{
			sh->dkey[k++] = *dollar;
			dollar++;
			sh->dollen++;
		}
		sh->dkey[k] = '\0';
	}
	if (line[*i] == 34) //"
	{
		(*i)++;
		sh->flag2++;
	write_args(sh, line, i, 34);
	}
	else if (line[*i] == 36) //$
		write_args(sh, line, i, '\0');
	else //'
	{
		sh->flag1++;
		sh->dollen = 0;
		(*i)++;
		write_args(sh, line, i, 39);
	}
}

static int init_massiv(t_shell *sh)
{
	int i;

	i = 0;
	if(!(sh->args_of_shell = malloc(sizeof(char*) * 200)))
		return (-1);
	while (i != 200)
		sh->args_of_shell[i++] = NULL;
	return (0);
}

int parse_shell(t_shell *sh, char *line, int i)
{
	init_massiv(sh);

//	printf("%s\n", line);
	while (line[i] != '\0')
	{
		while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			   || (line[i] == '\r' || line[i] == '\v' || line[i] == '\f'))
			i++;
		if (line[i] == 34 || line[i] == 39 || line[i] == 36)
			if_find_elem(line, &i, sh);
		else
			write_args(sh, line, &i, ' ');
		if (line[i] == ' ')
			sh->numargs++;
	}
	commands(sh->args_of_shell);
	// int z = 0;
	// while (z <= sh->numargs + 1)
	// {
	// 	printf("aos[%d] |%s|\n", z, sh->args_of_shell[z]);
	// 	z++;
	// }
	free(sh->args_of_shell);
	return (0);
}