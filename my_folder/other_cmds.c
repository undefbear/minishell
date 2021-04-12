/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:54:04 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 17:23:59 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static char	*cheack_path_2(char *cmd, char *path)
{
	char	*name;
	char	*file;
	int		fd;

	name = finde_new_path(&path);
	while (name)
	{
		file = ft_strjoin(name, cmd);
		fd = open(file, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			free(path);
			free(name);
			return (file);
		}
		free(name);
		free(file);
		name = finde_new_path(&path);
	}
	free(path);
	free(name);
	return (NULL);
}

char	*cheack_path(char *cmd)
{
	char	*path;

	path = ft_strdup(find_list(g.root, "PATH"));
	if (path)
		return (cheack_path_2(cmd, path));
	return (NULL);
}

int	check_slesh(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 1 && str[0] == '/')
		return (1);
	if (len > 2 && (str[0] == '.' && str[1] == '/'))
		return (1);
	if (len > 3 && (str[0] == '.' && str[1] == '.' && str[2] == '/'))
		return (1);
	return (0);
}

static void	other_cmd_without_slesh_2(char **cmd, char **env, char *cmd_name)
{
	char	*n_cmd;
	int		rv;

	n_cmd = cheack_path(cmd[0]);
	if (n_cmd)
	{
		g.pid = fork();
		if (g.pid == 0)
			exit(execve(n_cmd, cmd, env));
		else
			waitpid(g.pid, &rv, 0);
		if (rv)
		{
			g.error_code[0] = '1';
			g.error_code[1] = 0;
		}
		free(n_cmd);
	}
	else
	{
		err_code127();
		print_error("minishell:  ", 0);
		print_error(cmd_name, 0);
		print_error(": command not found\n", 0);
	}	
}

void	other_cmd_without_slesh(char **cmd)
{
	char	**env;
	char	*cmd_name;

	if (!cmd[0][0])
	{
		err_code127();
		print_error("minishell:  : command not found\n", 0);
		return ;
	}
	cmd_name = cmd[0];
	env = env_to_args();
	other_cmd_without_slesh_2(cmd, env, cmd_name);
	ft_split_free(env);
	g.pid = 0;
}
