#include "../include/shell.h"


int		ft_putchar(int c)
{
	return (write(0, &c, 1));
}


static void	ft_change_value(char **res, char *value, int flag)
{
	char		*tmp;

	if (flag)
	{
		tmp = *res;
		*res = ft_strjoin(*res, value);
		free(tmp);
	}
	else
	{
		free(*res);
		*res = ft_strdup(value);
	}
}

static	void	delete_sym(char **res, int num)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(*res));
	i = -1;
	while ((*res)[++i])
	{
		if (i < num - 1)
			str[i] = (*res)[i];
		else if (i == num - 1)
			continue;
		else
			str[i - 1] = (*res)[i];
	}
	str[i - 1] = 0;
	free(*res);
	*res = str;
}

void	pos_curs(int *row, int *col)
{
	char	pos[20];
	int		i;

	ft_bzero(pos, 20);
	write(0, "\e[6n", ft_strlen("\e[6n"));
	i = read(0, pos, 20);
	pos[i] = 0;
	i = 2;
	*row = ft_atoi(pos + i);
	while (ft_isdigit(pos[i]))
		i++;
	*col = ft_atoi(pos + i + 1);
}


void		read_sym(char str[2000], char **res, t_hist	**hist)
{
	int		l;

	l = read(0, str, 100);
	str[l] = 0;
	int col, row;
	col = 0;
	row = 0;
	pos_curs(&row, &col);
	if (equals(str, "\e[A"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (!*hist)
			*hist = g.head;
		put_srt((*hist)->value);
		ft_change_value(res, (*hist)->value, 0);
		*hist = (*hist)->next;
	}
	else if (equals(str, "\e[B"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (!*hist)
			*hist = g.tail;
		put_srt((*hist)->value);
		ft_change_value(res, (*hist)->value, 0);
		*hist = (*hist)->prev;
	}
	else if (equals(str, "\e[C"))
	{
		if (col < 13 + ft_strlen(*res))
			write(1, str, l);
	}
	else if (equals(str, "\e[D"))
	{
		if (col > 13)
			write(1, str, l);
	}
	else if (equals(str, "\177"))
	{
		if (col > 13)
		{
			delete_sym(res, col - 13);
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
		}
	}
	else if  (equals(str, "\n"))
		write(1, str, l);
	else
	{
		write(1, str, l);
		ft_change_value(res, str, 1);
	}
}


int		*gnl_v2(char **res)
{
	char	str[2000];
	int		l;
	struct termios term;
	char	*name;
	t_hist	*hist;

	hist = g.head;
	ft_bzero(str, sizeof(char) * 2000);
	name = find_list(g.root, "TERM");
	tcgetattr(0, &term);
	if (!name)
	{
		printf("cant to find TERM in env, pls add this param\n");
		return (0);
	}
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	l = tgetent(0, name);
	if (l <= 0)
	{
		printf("parm TERM is wrong or smth else\n");
		return (0);
	}
	*res = NULL;
	write(0, "minishell:  ", 12);
	tputs(save_cursor, 1, ft_putchar);
	read_sym(str, res, &hist);
	while (!equals(str, "\n"))
		read_sym(str, res, &hist);
	if (!*res)
		*res = ft_strdup("");
	if (ft_strlen(*res))
		hist_add(&g.head, &g.tail, ft_strdup(*res));
	// printf("%s\n", *res);
	return 0;
}