/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/24 17:41:22 by ealexa           ###   ########.fr       */
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

	path = ft_strdup(find_list(g.root, "PATH"));
	while ((name = finde_new_path(&path)))
	{
		file = ft_strjoin(name, cmd);
		fd = open(file, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			free(path);
			return (file);
		}
		free(name);
		free(file);
	}
	free(path);
	return (NULL);
}

void	cmd_pwd()
{
	write(0, find_list(g.root, "PWD"), ft_strlen(find_list(g.root, "PWD")));
	write(0, "\n", 1);
}

void	cd_pwd()
{
	write(0, find_list(g.root, "PWD"), ft_strlen(find_list(g.root, "PWD")));
	write(0, "\n", 1);
}

void	other_cmd_without_slesh(char *cmd)
{
	char	**env;
	char	**argv;
	char	*n_cmd;
	
	env = env_to_args();
	argv = malloc(sizeof(char*) * 3);
	n_cmd = cheack_path(cmd);
	argv[0] = ft_strdup(find_list(g.root, "PATH"));
	argv[1] = 0;
	// execve(n_cmd, argv, env);
	env = ft_split_free(env);
}

void	commands(char *cmd)
{
	if (!ft_strncmp(cmd, PWD, ft_strlen(PWD)))
		cmd_pwd();
	else if (!ft_strncmp(cmd, CD, ft_strlen(CD)))
		cd_pwd();
	else
		other_cmd_without_slesh(cmd);
}

int main(int argc, char *argv[], char **envp)
{
	init_env(&g.root, envp);
	g.argv = argv;
	t_list *next = g.root;
	printf("----------------------------------\n");
	commands("ls");
	printf("----------------------------------\n");
	delete_list(&g.root);
	return (0);
}
