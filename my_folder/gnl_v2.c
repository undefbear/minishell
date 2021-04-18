/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_v2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/18 11:12:05 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	delete_sym(char **res, int col)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(*res));
	ft_bzero(str, sizeof(char) * ft_strlen(*res));
	i = -1;
	if (!col)
	{
		while (++i < ft_strlen(*res) - 1)
			str[i] = (*res)[i];
		str[i] = 0;
		free(*res);
		*res = str;
	}
	else
	{
		while (++i < ft_strlen(*res) - col - 1)
			str[i] = (*res)[i];
		while (++i < ft_strlen(*res))
			str[i - 1] = (*res)[i];
		str[i - 1] = 0;
		free(*res);
		*res = str;
	}
}

void	read_sym(char str[BUFF_SIZE], char **res, t_hist	**hist, int *col)
{
	int		l;

	g_gl.res = res;
	l = read(0, str, BUFF_SIZE);
	str[l] = 0;
	g_gl.col = tgetnum("co");
	if (equals(str, "\e[A"))
		press_key_up(hist, res, col);
	else if (equals(str, "\e[B"))
		press_key_down(hist, res, col);
	else if (equals(str, "\e[C"))
		press_key_right(res, col, l, str);
	else if (equals(str, "\e[D"))
		press_key_left(res, col, l, str);
	else if (equals(str, "\177"))
		press_key_delete(res, col);
	else if (equals(str, "\n"))
		press_enter(col, res, str, l);
	else if (equals(str, "\x04"))
		press_sigint(res);
	else
		press_other(str, res, col);
}

void	term_init(void)
{
	char			*name;
	int				l;

//	name = find_list(g_gl.root, "TERM");
	name = "xterm-256color";
	ft_bzero(&g_gl.term, sizeof(struct termios));
	tcgetattr(0, &g_gl.term);
	if (!name)
	{
		print_error("cant to find TERM in env, pls add this param\n", 0);
		cmd_exit(NULL);
	}
	g_gl.term.c_lflag &= ~(ECHO);
	g_gl.term.c_lflag &= ~(ICANON);
	g_gl.term.c_cc[VTIME] = 0;
	g_gl.term.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &g_gl.term);
	l = tgetent(0, name);
	if (l <= 0)
	{
		print_error("parm TERM is wrong or smth else\n", 0);
		cmd_exit(NULL);
	}
}

void	term_back_normal(void)
{
	tcgetattr(0, &g_gl.term);
	g_gl.term.c_lflag |= (ECHO);
	g_gl.term.c_lflag |= (ICANON);
	tcsetattr(0, TCSADRAIN, &g_gl.term);
}

int	*gnl_v2(char **res)
{
	char			str[BUFF_SIZE];
	int				col;
	t_hist			*hist;

	g_gl.cmd = NULL;
	g_gl.new_cmd = NULL;
	term_init();
	g_gl.col = tgetnum("co");
	col = 0;
	hist = g_gl.head;
	ft_bzero(str, sizeof(char) * BUFF_SIZE);
	*res = ft_strdup("");
	write(1, "minishell:   ", 12);
	tputs(save_cursor, 1, ft_putchar);
	read_sym(str, res, &hist, &col);
	while (!equals(str, "\n") && !g_gl.flag)
		read_sym(str, res, &hist, &col);
	if (!*res)
		*res = ft_strdup("");
	if (ft_strlen(*res))
		hist_add(&g_gl.head, &g_gl.tail, ft_strdup(*res));
	term_back_normal();
	return (NULL);
}
