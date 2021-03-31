#include "../include/mine.h"

//длина строки для записи в массив
int find_lenght(char *line, char till, int i)
{
	int len;

	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == till)
		{
			if (till != ' ')
				len += 2;
			break;
		}
		len++;
		i++;
	}
	return (len);
}

//поиск зачения по ключу
int find_value(t_shell *sh)
{
	int len;

	len = 0;
	if (sh->dollen)
	{
		if (sh->evkey[0] == '?')
			sh->evvalue = g.error_code;
		else
			sh->evvalue = find_list(g.root, sh->evkey);
		if (sh->evvalue)
			len = ft_strlen(sh->evvalue);
		else
			len = 0;
	}
	return(len);
}

char *init_array(t_shell *sh, int linelen)
{
	int tmplen;
	char *tmp;

	tmp = NULL;
	tmplen = 0;
	if (!sh->args_of_shell[sh->numargs])
	{
		if (!(sh->args_of_shell[sh->numargs] = malloc(
				sizeof(char *) * (linelen - sh->dollen + sh->valuelen) + 1)))
			return (tmp);
	}
	else
	{
		tmplen = ft_strlen(sh->args_of_shell[sh->numargs]);
		if (!(tmp = malloc(tmplen)))
			return (tmp);
		tmp = sh->args_of_shell[sh->numargs];
		if (!(sh->args_of_shell[sh->numargs] = malloc(
				sizeof(char *) * (linelen - sh->dollen + sh->valuelen) + 1)))
			return (tmp);
	}
	return(tmp);
}

int create_words(t_shell *sh, char *line, int *i)
{
	if ((line[*i] == 34) && (sh->flag2 == 0 || sh->flag2 % 2 == 0))
			return (-1);
	else if ((line[*i] == 34) && (sh->flag2 != 0 || sh->flag2 % 2 != 0))
	{
			(*i)++;
			return (1);
	}
	else if ((line[*i] == 39) && (sh->flag1 == 0 || sh->flag1 % 2 == 0))
			return (-1);
	else if ((line[*i] == 39) && (sh->flag1 != 0 || sh->flag1 % 2 != 0))
	{
		(*i)++;
		return (1);
	}
	else if (line[*i] == 32 && sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0)
	{
		sh->dollen = 0;
		return (-1);
	}
	return (0);
}

//int create_env(t_shell *sh, int *z, int *k, int linelen)
//{
//	*i += sh->dollen;
//	linelen = linelen - sh->dollen;
//	while (sh->valuelen-- != 0)
//		sh->args_of_shell[sh->numargs][z++] = sh->evvalue[k++];
//}

//
int correct_env_var(char c)
{
	if ((c != '\0' && c != ' ') &&
	((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		return (0);
	else
		return (1);
}

