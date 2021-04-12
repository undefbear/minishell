/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sym.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:54:04 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 16:27:02 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	press_key_delete_2(char **res, int *col)
{
	int	i;

	tputs(cursor_left, 1, ft_putchar);
	tputs(delete_character, 1, ft_putchar);
	delete_sym(res, *col);
	if (*col)
	{
		tputs(tigetstr("ed"), 1, ft_putchar);
		i = ft_strlen(*res) - *col - 1;
		while (i++ < ft_strlen(*res))
			write(0, (*res + i), 1);
		i = -1;
		while (++i < *col)
			tputs(cursor_left, 1, ft_putchar);
	}	
}

static void	press_key_delete_3(char **res, int *col)
{
	int	i;

	i = -1;
	if (((ft_strlen(*res) + 12 + g.echon) % g.col) - *col == 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		write(0, *res + (ft_strlen(*res) - 2), 1);
		tputs(cursor_right, 1, ft_putchar);
		delete_sym(res, *col);
		if (*col)
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			put_srt(*res);
			while (++i < *col)
				tputs(cursor_left, 1, ft_putchar);
		}
	}
	else
		press_key_delete_2(res, col);
}

void	press_key_delete(char **res, int *col)
{
	g.col = tgetnum("co");
	if (ft_strlen(*res) - *col)
		press_key_delete_3(res, col);
}
