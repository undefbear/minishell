/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:54:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/30 16:50:14 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void		cmd_cd_2(char **cmd, char **path)
{
	char buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	if (!(char*)buff)
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		printf("Some error!!!\n");
	}
	path[1] = ft_strjoin("OLDPWD=", buff);
	if (chdir(cmd[1]) == -1)
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		printf("cd: no such file or directory: %s\n", cmd[1]);
		ft_split_free(path);
		return ;
	}
	commands(path);
	free(path[1]);
	getcwd(buff, PATH_MAX);
	path[1] = ft_strjoin("PWD=", buff);
	commands(path);
	ft_split_free(path);
}

void			cmd_cd(char **cmd)
{
	char **path;
	char buff[PATH_MAX];

	g.error_code[0] = '0';
	g.error_code[1] = 0;
	path = malloc(sizeof(char*) * 3);
	path[0] = ft_strdup("export");
	path[2] = 0;
	if (arr_size(cmd) == 1)
	{
		if (find_list(g.root, "HOME"))
		{
			getcwd(buff, PATH_MAX);
			if (!(char*)buff)
			{
				g.error_code[0] = '1';
				g.error_code[1] = 0;
				printf("Some error!!!\n");
			}
			path[1] = ft_strjoin("OLDPWD=", buff);
			if (chdir(find_list(g.root, "HOME")) == -1)
			{
				g.error_code[0] = '1';
				g.error_code[1] = 0;
				printf("cd: no such file or directory:\n");
				path = ft_split_free(path);
				return ;
			}
			commands(path);
			free(path[1]);
			getcwd(buff, PATH_MAX);
			path[1] = ft_strjoin("PWD=", buff);
			commands(path);
			path = ft_split_free(path);
		}
		else
		{
			g.error_code[0] = '1';
			g.error_code[1] = 0;
			printf("/usr/bin/CD: line 4: cd: HOME not set\n");
		}
	}
	else if (arr_size(cmd) == 2)
		cmd_cd_2(cmd, path);
	else
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		printf("cd: string not in pwd: %s\n", cmd[1]);
	}
}