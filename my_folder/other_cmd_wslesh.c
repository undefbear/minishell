/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd_wslesh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:24:45 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/17 16:21:58 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*finde_new_path(char **path)
{
	char	*f;
	char	*res;
	char	*tmp;

	f = ft_strrchr(*path, ':');
	if (!f)
		return (NULL);
	*f = '\0';
	res = ft_strdup(++f);
	tmp = res;
	res = ft_strjoin(res, "/");
	free(tmp);
	return (res);
}

static int	check_filea(char **cmd)
{
	int	res;

	res = open(cmd[0], O_RDONLY);
	if (res > 0)
	{
		close(res);
		return (0);
	}
	else
	{
		err_code127();
		print_error("minishell:  ", 0);
		print_error(cmd[0], 0);
		print_error(": No such file or directory\n", 0);
		return (1);
	}
}

static void	check_error (int rv)
{
	if (g_gl.error_code[0] == '0')
		arg_itoa(rv);
}

static void	other_cmd_with_slesh(char **cmd)
{
	int		rv;
	char	**env;

	rv = check_filea(cmd);
	if (rv)
		return ;
	env = env_to_args();
	g_gl.pid = fork();
	if (g_gl.pid == 0)
		exit(execve(cmd[0], cmd, env));
	else
		waitpid(g_gl.pid, &rv, 0);
	if (rv)
		check_error(rv);
	env = ft_split_free(env);
	g_gl.pid = 0;
}

void	other_cmd(char **cmd)
{
	if (check_slesh(cmd[0]))
		other_cmd_with_slesh(cmd);
	else
		other_cmd_without_slesh(cmd);
}
