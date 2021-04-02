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
			len++;
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

char *init_array(t_shell *sh)
{
	int tmplen;
	char *tmp;

	tmp = NULL;
	tmplen = 0;
	if (!sh->args_of_shell[sh->numargs])
	{
		if (!(sh->args_of_shell[sh->numargs] = malloc(sizeof(char *) *
			(sh->lenght - sh->dollen + sh->valuelen) + 1)))
			return (tmp);
	}
	else
	{
//		tmplen = ft_strlen(sh->args_of_shell[sh->numargs]);
//		if (!(tmp = malloc(tmplen)))
//			return (tmp);
		tmp = ft_strdup(sh->args_of_shell[sh->numargs]);
		free(sh->args_of_shell[sh->numargs]);
		sh->args_of_shell[sh->numargs] = NULL;
		if (!(sh->args_of_shell[sh->numargs] = malloc(sizeof(char *)
				* (sh->lenght - sh->dollen + sh->valuelen) + 1)))
			return (NULL); //todo
	}
	return(tmp);
}

//запись имени ключа в переменную
int init_env_var(char *env_variable, t_shell *sh)
{
	int len;
	int i;
	int k;

	i = 1;
	k = 0;
	len = 0;
	if (env_variable[i] == '?')
		len = 1;
	else
		while (!(its_env_var(env_variable[i])))
		{
			i++;
			len++;
		}
	if (!(sh->evkey = malloc(sizeof(char*) * len + 1)))
		return (-1);
	sh->dollen = len + 1;
	i = 1;
	while (len-- != 0)
		sh->evkey[k++] = env_variable[i++];
	sh->evkey[k] = '\0';
	sh->valuelen = find_value(sh);
	return (0);
}

int init_first_pointer(t_shell *sh)
{
	if (!(sh->args_of_shell = malloc(sizeof(char *) * 2)))
		return (-1);
	sh->args_of_shell[0] = NULL;
	sh->args_of_shell[1] = NULL;
	return (0);
}
