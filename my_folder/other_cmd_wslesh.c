/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd_wslesh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:24:45 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/02 20:58:30 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	other_cmd_with_slesh(char **cmd)
{
	int		rv;
	char	**env;

	env = env_to_args();
    g.pid = fork();
	if (g.pid == 0)
		exit(execve(cmd[0], cmd, env));
	else
		waitpid(g.pid, &rv, 0);
	if (rv)
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		write(0, "minishell: ", 11);
		put_srt(cmd[0]);
		write(0, ": No such file or directory\n", 28);
		// printf("minishell: %s: No such file or directory\n", cmd[0]);
	}
	else
	{
		g.error_code[0] = '0';
		g.error_code[1] = 0;
	}
	env = ft_split_free(env);
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

	if (!cmd[0][0])
    {
        g.error_code[0] = '1';
        g.error_code[1] = '2';
        g.error_code[2] = '7';
        g.error_code[3] = 0;
        printf("minishell: : command not found\n");
        return ;
    }
	cmd_name = cmd[0];
	env = env_to_args();
	if ((n_cmd = cheack_path(cmd[0])))
	{
		int rv;
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
		else
		{
			g.error_code[0] = '0';
			g.error_code[1] = 0;
		}
		free(n_cmd);
		env = ft_split_free(env);
	}
	else
	{
		g.error_code[0] = '1';
		g.error_code[1] = '2';
		g.error_code[2] = '7';
		g.error_code[3] = 0;
		printf("minishell:  %s: command not found\n", cmd_name);
	}
}

int		check_slesh(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 1 && str[0] == '/')
		return (1);
	if (len > 2 && (str[0] == '.' && str[1] == '/'))
		return (1);
	if (len > 3 && (str[0] == '.' && str[1] == '.' && str[2] == '/'))
		return (1);
	return (0);
}

void	other_cmd(char **cmd)
{
	if (check_slesh(cmd[0]))
		other_cmd_with_slesh(cmd);
	else
		other_cmd_without_slesh(cmd);
}
