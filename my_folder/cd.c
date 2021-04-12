/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:54:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 14:39:17 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	cmd_cd_2(char **cmd, char **path)
{
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	if (!buff[0])
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		print_error("Some error!!!\n", 0);
	}
	path[1] = ft_strjoin("OLDPWD=", buff);
	if (chdir(cmd[1]) == -1)
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		print_error("minishell:  cd: no such file or directory: ", 0);
		print_error(cmd[1], 1);
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

static	void	error_mess(char *str)
{
	err_code1();
	print_error(str, 0);
}

static void	cmd_home(char **path, char buff[PATH_MAX])
{
	if (find_list(g.root, "HOME"))
	{
		getcwd(buff, PATH_MAX);
		if (!buff[0])
			error_mess("Some error!!!\n");
		path[1] = ft_strjoin("OLDPWD=", buff);
		if (chdir(find_list(g.root, "HOME")) == -1)
		{
			error_mess("Some error!!!\n");
			err_code1("minishell:  cd: no such file or directory\n");
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
		error_mess("minishell:  /usr/bin/CD: line 4: cd: HOME not set\n");
}

void	cmd_cd(char **cmd)
{
	char	**path;
	char	buff[PATH_MAX];

	path = malloc(sizeof(char *) * 3);
	path[0] = ft_strdup("export");
	path[2] = 0;
	if (arr_size(cmd) == 1)
		cmd_home(path, buff);
	else if (arr_size(cmd) == 2)
		cmd_cd_2(cmd, path);
	else
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		print_error("minishell:  cd: string not in pwd: ", 0);
		print_error(cmd[1], 1);
	}
}
