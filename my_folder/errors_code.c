/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:44:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 16:53:44 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	print_error(char *cmd, int f)
{
	write(2, cmd, ft_strlen(cmd));
	if (f)
		write(2, "\n", 1);
}

void	err_code127(void)
{
	g.error_code[0] = '1';
	g.error_code[1] = '2';
	g.error_code[2] = '7';
	g.error_code[3] = 0;
}

void	err_code1(void)
{
	g.error_code[0] = '1';
	g.error_code[1] = 0;
}
