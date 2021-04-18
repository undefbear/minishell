#include "../include/shell.h"

//длина строки для записи в массив
int	find_lenght(char *line, char till, int i)
{
	int	len;

	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == till)
		{
			if (till != ' ')
				len += 2;
			len++;
			break ;
		}
		len++;
		i++;
	}
	return (len);
}

//поиск зачения по ключу
int	find_value(t_shell *sh)
{
	int	len;

	len = 0;
	if (sh->dollen)
	{
		if (sh->evkey[0] == '?')
			sh->evvalue = g_gl.error_code;
		else
			sh->evvalue = find_list(g_gl.root, sh->evkey);
		if (sh->evvalue)
			len = ft_strlen(sh->evvalue);
		else
			len = 0;
	}
	return (len);
}

//выделение памяти под аргумент
char	*init_array(t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	if (!sh->args_of_shell[sh->numargs])
	{
		sh->args_of_shell[sh->numargs] = malloc(sizeof(char *)
				* (sh->lenght - sh->dollen + sh->valuelen) + 1);
		if (!(sh->args_of_shell[sh->numargs]))
			cmd_exit(NULL);
	}
	else
	{
		tmp = ft_strdup(sh->args_of_shell[sh->numargs]);
		free(sh->args_of_shell[sh->numargs]);
		sh->args_of_shell[sh->numargs] = NULL;
		sh->args_of_shell[sh->numargs] = malloc(sizeof(char *)
				* (sh->lenght - sh->dollen + sh->valuelen) + 1);
		if (!(sh->args_of_shell[sh->numargs]))
			cmd_exit(NULL);
	}
	return (tmp);
}

//длина ключа перменной окружения
int	find_ev_len(char *e_v)
{
	int	z;
	int	len;

	z = 1;
	len = 0;
	if (e_v[z] == '?')
		len = 1;
	else
	{
		while (((e_v[z] != '\0' && e_v[z] != ' ')
				&& ((e_v[z] >= 48 && e_v[z] <= 57)
					|| (e_v[z] >= 65 && e_v[z] <= 90)
					|| (e_v[z] >= 97 && e_v[z] <= 122))))
		{
			z++;
			len++;
		}
	}
	return (len);
}

//запись имени ключа в переменную
int	init_env_var(char *env_variable, t_shell *sh, int *i)
{
	int	len;
	int	z;
	int	k;

	k = 0;
	len = find_ev_len(env_variable);
	if (!len)
	{
		(*i)++;
		return (0);
	}
	sh->evkey = malloc(sizeof(char *) * len + 1);
	if (!sh->evkey)
		cmd_exit(NULL);
	sh->dollen = len + 1;
	z = 1;
	while (len-- != 0)
		sh->evkey[k++] = env_variable[z++];
	sh->evkey[k] = '\0';
	sh->valuelen = find_value(sh);
	return (0);
}
