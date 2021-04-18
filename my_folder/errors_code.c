/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:44:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/17 16:21:33 by ealexa           ###   ########.fr       */
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
	g_gl.error_code[0] = '1';
	g_gl.error_code[1] = '2';
	g_gl.error_code[2] = '7';
	g_gl.error_code[3] = 0;
}

void	err_code1(void)
{
	g_gl.error_code[0] = '1';
	g_gl.error_code[1] = 0;
}
