/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:41:31 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/27 15:06:24 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_echo_n(char **cmd)
{
	int i;

	i = 1;
	while (cmd[++i])
	{
		if (cmd[i + 1])
			printf("%s ", cmd[i]);
		else
			printf("%s", cmd[i]);		
	}
}

void	cmd_echo_not_n(char **cmd)
{
	int i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i + 1])
			printf("%s ", cmd[i]);
		else
			printf("%s\n", cmd[i]);		
	}
}

void	cmd_echo(char **cmd)
{
	g.error_code = 0;
	if (arr_size(cmd) == 1)
		printf("\n");
	else if (equals(cmd[1], "-n"))
		cmd_echo_n(cmd);
	else
		cmd_echo_not_n(cmd);
}
