#include "../include/mine.h"

//подготовка массива к записи токенов
int prepare_array(t_shell *sh, char *line, int *i, char till)
{
	char *tmp;

	tmp = NULL;
	sh->lenght = find_lenght(line, till, (*i));
	if (sh->numargs != 0 && sh->args_of_shell[sh->numargs - 1][0] == 0)
		sh->numargs--;
	tmp = init_array(sh);
	create_tokens(sh, line, i);
	if (tmp)
	{
		sh->args_of_shell[sh->numargs]
		= ft_strjoin(tmp, sh->args_of_shell[sh->numargs]);
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
	if (line[*i] == 34) //"
	{
		(*i)++;
		sh->flag2++;
		prepare_array(sh, line, i, 34);
	}
	else if (line[*i] == 39) //'
	{
		sh->flag1++;
		(*i)++;
		prepare_array(sh, line, i, 39);
	}
	else if (line[*i] == 36) //$
	{
		if ((sh->flag1 % 2 != 0) && (sh->flag2 % 2 == 0))
			sh->dollen = -1;
		else
			init_env_var(&line[*i], sh);
		prepare_array(sh, line, i, '\0');
	}
}

char **create_tmp(t_shell *sh)
{
	char **tmp;
	int i;
	int w;

	i = 0;
	w = sh->numargs;
	if (!(tmp = malloc(sizeof(char *) * w + 1)))
		return (NULL); //todo
	while (w-- != 0)
	{
		tmp[i] = sh->args_of_shell[i];
		i++;
	}
	tmp[i] = NULL;
	return(tmp);
}

int init_new_pointer(t_shell *sh)
{
	int new_num_lines;
	char **tmp;
	int i;

	i = 0;
	new_num_lines = sh->numargs + 1;
	tmp = create_tmp(sh);
	free(sh->args_of_shell);
	sh->args_of_shell = NULL;
	if (!(sh->args_of_shell = malloc(sizeof(char *) * new_num_lines + 1)))
		return (-1);
	new_num_lines--;
	while(new_num_lines-- != 0)
	{
		sh->args_of_shell[i] = tmp[i];
		i++;
	}
	sh->args_of_shell[i++] = NULL;
	sh->args_of_shell[i] = NULL;
	free(tmp);
	return (0);
}

int parse_shell(t_shell *sh, char *line, int i)
{
//	printf("%s\n", line);
	init_first_pointer(sh);
	while (line[i] != '\0')
	{
		while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			   || (line[i] == '\r' || line[i] == '\v' || line[i] == '\f'))
			i++;
		if (line[i] == 34 || line[i] == 39 || line[i] == 36)
			if_find_elem(line, &i, sh);
		else
			prepare_array(sh, line, &i, ' ');
		if ((line[i] == 32) || (line[i] == 59))
			change_pos(sh, line[i], &i);
	}
	commands(sh->args_of_shell);
//	int z = 0;
//	while (z <= sh->numargs + 1)
//	{
//		printf("aos[%d] |%s|\n", z, sh->args_of_shell[z]);
//		z++;
//	}
	return (0);
}