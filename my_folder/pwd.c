/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:23:54 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/27 14:30:11 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_pwd(char **cmd)
{
	char buff[PATH_MAX];

	if (arr_size(cmd) != 1)
	{
		g.error_code = 1;
		put_srtln("minishell: pwd: too many arguments");
		return ;
	}
	getcwd(buff, PATH_MAX);
	if (!buff[0])
	{
		g.error_code = 1;
		printf("Some error!!!\n");
		return ;
	}
	g.error_code = 0;
	printf("%s\n", buff);
}
