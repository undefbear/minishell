/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd_wslesh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:24:45 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/25 18:28:03 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*finde_new_path(char **path)
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

char	*cheack_path(char *cmd)
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

void	other_cmd_without_slesh(char **cmd)
{
	char	**env;
	char	*n_cmd;
	char	*cmd_name;

	cmd_name = cmd[0];
	env = env_to_args();
	if ((n_cmd = cheack_path(cmd[0])))
	{
		if (!n_cmd)
		{
			put_srt("zsh: command not found: ");
			put_srtln(cmd_name);
		}
		else
		{
			pid_t pid;
			int rv;
			pid = fork();
			if (pid == 0)
				exit(execve(n_cmd, cmd, env));
			else
				waitpid(pid, &rv, 0);
		}
		free(n_cmd);
		env = ft_split_free(env);
	}
	else
	{
		put_srt("zsh: command not found: ");
		put_srtln(cmd_name);	
	}
}
