#include "../include/mine.h"

//подготовка массива к записи токенов
int prepare_array(t_shell *sh, char *line, int *i, char till)
{
	int linelen;
	char *tmp;

	linelen = find_lenght(line, till, (*i));
	sh->valuelen = find_value(sh);
	if (sh->numargs != 0 && sh->args_of_shell[sh->numargs - 1][0] == 0)
		sh->numargs--;
	tmp = init_array(sh, linelen);
	create_tokens(sh, line, i, linelen);
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
	char *env_variable;

	env_variable = NULL;
	if ((env_variable = ft_strchr(&line[*i], 36)))
		init_env_var(env_variable, sh);
	if (line[*i] == 34) //"
	{
		(*i)++;
		sh->flag2++;
		prepare_array(sh, line, i, 34);
	}
	else if (line[*i] == 36) //$
		prepare_array(sh, line, i, '\0');
	else //'
	{
		sh->flag1++;
		sh->dollen = 0;
		(*i)++;
		prepare_array(sh, line, i, 39);
	}
}

static int init_pointers(t_shell *sh)
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
	init_pointers(sh);
//	printf("%s\n", line);
	while (line[i] != '\0')
	{
		while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			   || (line[i] == '\r' || line[i] == '\v' || line[i] == '\f'))
			i++;
		if (line[i] == 34 || line[i] == 39 || line[i] == 36)
			if_find_elem(line, &i, sh);
		else
			prepare_array(sh, line, &i, ' ');
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