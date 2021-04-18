/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:23:54 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/17 16:22:12 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_pwd(void)
{
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	if (!buff[0])
	{
		g_gl.error_code[0] = '1';
		g_gl.error_code[1] = 0;
		print_error("Some error!!!\n", 0);
		return ;
	}
	g_gl.error_code[0] = '0';
	g_gl.error_code[1] = 0;
	printf("%s\n", buff);
}
