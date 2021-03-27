/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/27 19:57:39 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_exit(char **cmd)
{
	if (arr_size(cmd) == 1)
	{
		delete_list(&g.root);
		delete_list(&g.export);
		exit(0);
	}
	else if (arr_size(cmd) > 2)
	{
		g.error_code = 1;
		printf("minishell: exit: too many arguments\n");
	}
	else
	{
		g.error_code = ft_atoi(cmd[1]);
		delete_list(&g.root);
		delete_list(&g.export);
		exit(g.error_code);	
	}
}

void	commands(char **cmd)
{
	if (equals(PWD, cmd[0]))
		cmd_pwd(cmd);
	else if (equals(CD, cmd[0]))
		cmd_cd(cmd);
	else if (equals(EXPORT, cmd[0]))
		cmd_export(cmd);
	else if (equals(ENV, cmd[0]))
		cmd_env(cmd);
	else if (equals(UNSET, cmd[0]))
		cmd_unset(cmd);
	else if (equals(ECHO, cmd[0]))
		cmd_echo(cmd);
	else if (equals(EXIT, cmd[0]))
		cmd_exit(cmd);
	else
		other_cmd(cmd);
}
