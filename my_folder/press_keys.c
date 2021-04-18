/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:54:04 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/17 16:22:08 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	press_key_up(t_hist **hist, char **res, int *col)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	if (!*hist)
		*hist = g_gl.head;
	put_srt((*hist)->value);
	ft_change_value(res, (*hist)->value, 0, *col);
	*hist = (*hist)->next;
}

void	press_key_down(t_hist **hist, char **res, int *col)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	if (!*hist)
		*hist = g_gl.tail;
	put_srt((*hist)->value);
	ft_change_value(res, (*hist)->value, 0, *col);
	*hist = (*hist)->prev;
}

void	press_key_right(char **res, int *col, int l, char str[2000])
{
	if (!((ft_strlen(*res) + 12 + g_gl.echon) % g_gl.col - *col))
	{
		(*col) -= 1;
		tputs(cursor_down, 1, ft_putchar);
		tputs(cursor_right, 1, ft_putchar);
	}
	else if (*col != 0)
	{
		(*col) -= 1;
		write(0, str, l);
	}
}

void	press_key_left(char **res, int *col, int l, char str[2000])
{
	if (*col < ft_strlen(*res))
	{
		(*col) += 1;
		write(0, str, l);
	}
}

void	press_enter(int *col, char **res, char str[2000], int l)
{
	int	i;
	int	k;

	if (*col)
	{
		i = (ft_strlen(*res) + g_gl.echon + 12 - *col) % g_gl.col;
		k = ((ft_strlen(*res) + g_gl.echon + 12) / g_gl.col)
			- ((ft_strlen(*res) + g_gl.echon + 12 - *col) / g_gl.col);
		while (i-- > 0)
			tputs(cursor_right, 1, ft_putchar);
		while (k-- > 0)
			tputs(cursor_down, 1, ft_putchar);
	}
	write(0, str, l);
}
