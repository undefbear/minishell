#include "../include/mine.h"

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
		while (!(correct_env_var(env_variable[i])))
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
	return (0);
}

//запись токенов в массив
int create_tokens (t_shell *sh, char *line, int *i, int linelen)
{
	int k;
	int z;

	k = 0;
	z = 0;
	while (linelen-- > 0)
	{
		if (line[(*i)] == 36 && sh->dollen)
		{
//			create_env(sh, &z, &k, linelen);
			*i += sh->dollen;
			linelen = linelen - sh->dollen;
			while (sh->valuelen-- != 0)
				sh->args_of_shell[sh->numargs][z++] = sh->evvalue[k++];
		}
		else
		{ //todo проверка на "" '' $$
			if (create_words(sh, line, i) == 1)
				break;
			else if (create_words(sh, line, i) == -1)
				return (0);
			else
			{
				if ((line[*i] == '\t' || line[*i] == '\n' || line[*i] == '\r'
					 || line[*i] == '\v' || line[*i] == '\f') &&
					(sh->flag2 % 2 == 0 && sh->flag1 % 2 == 0))
					line[*i] = ' ';
				else
					sh->args_of_shell[sh->numargs][z++] = line[(*i)++];
			}
		}
	}
	sh->args_of_shell[sh->numargs][z] = '\0';
}