/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd_wslesh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:24:45 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/27 14:39:11 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	other_cmd_with_slesh(char **cmd)
{
	pid_t	pid;
	int		rv;
	char	**env;

	env = env_to_args();
	pid = fork();
	if (pid == 0)
		exit(execve(cmd[0], cmd, env));
	else
		waitpid(pid, &rv, 0);
	if (rv)
		g.error_code = 1;
	else
		g.error_code = 0;
}


static char	*finde_new_path(char **path)
{
	char	*f;
	char	*res;
	char	*tmp;

	if (!(f = ft_strrchr(*path, ':')))
		return (NULL);	
	*f = '\0';
	res = ft_strdup(++f);
	tmp = res;
	res = ft_strjoin(res, "/");
	free(tmp);	
	return (res);
}

static char	*cheack_path(char *cmd)
{
	char	*path;
	char	*name;
	char	*file;
	int		fd;

	if ((path = ft_strdup(find_list(g.root, "PATH"))))
	{
		while ((name = finde_new_path(&path)))
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
		}
		free(path);
		free(name);	
		return (NULL);
	}
	return (NULL);
}

static void	other_cmd_without_slesh(char **cmd)
{
	char	**env;
	char	*n_cmd;
	char	*cmd_name;

	cmd_name = cmd[0];
	env = env_to_args();
	if ((n_cmd = cheack_path(cmd[0])))
	{
		pid_t pid;
		int rv;
		pid = fork();
		if (pid == 0)
			exit(execve(n_cmd, cmd, env));
		else
			waitpid(pid, &rv, 0);
		if (rv)
			g.error_code = 1;
		else
			g.error_code = 0;
		free(n_cmd);
		env = ft_split_free(env);
	}
	else
	{
		g.error_code = 127;
		printf("minishell: command not found: %s\n", cmd_name);
	}
}

void	other_cmd(char **cmd)
{
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		other_cmd_with_slesh(cmd);
	else
		other_cmd_without_slesh(cmd);
}
