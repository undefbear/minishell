/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/30 16:54:09 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_exit(char **cmd)
{
	unsigned char exit_code;

	if (arr_size(cmd) == 1)
	{
		delete_list(&g.root);
		delete_list(&g.export);
		exit(0);
	}
	else if (arr_size(cmd) > 2)
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		printf("minishell: exit: too many arguments\n");
	}
	else
	{
		exit_code = ft_atoi(g.error_code);
		delete_list(&g.root);
		delete_list(&g.export);
		exit(exit_code);
	}
}

void	commands(char **cmd)
{
	if (arr_size(cmd))
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
		else if (equals(_ECHO, cmd[0]))
			cmd_echo(cmd);
		else if (equals(EXIT, cmd[0]))
			cmd_exit(cmd);
		else
			other_cmd(cmd);		
	}
	// else
		// printf("\n");
}
