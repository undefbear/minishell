/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/17 16:21:55 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_putchar(int c)
{
	int	i;

	i = write(0, &c, 1);
	return (i);
}

void	cmd_auth(void)
{
	printf("--------------------------------\n");
	printf("|  semiteam: ealexa && kstout  |\n");
	printf("--------------------------------\n");
}

void	press_sigint(char **res)
{
	if (!ft_strlen(*res))
	{
		free(*res);
		*res = ft_strdup("exit");
		g_gl.flag = 1;
	}
}

void	press_other(char str[2000], char **res, int *col)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup(str);
	ft_change_value(res, tmp, 1, *col);
	free(tmp);
	if (*col)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		put_srt(*res);
		while (++i < *col)
			tputs(cursor_left, 1, ft_putchar);
	}
	else
	{
		while (str[++i])
		{
			if (ft_isprint(str[i]))
				write(0, &str[i], 1);
		}
	}
}
