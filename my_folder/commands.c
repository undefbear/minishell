/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/31 13:55:18 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	commands(char **cmd)
{
	if (arr_size(cmd))
	{
		g.error_code[0] = '0';
		g.error_code[1] = 0;
		if (equals(PWD, cmd[0]))
			cmd_pwd();
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
