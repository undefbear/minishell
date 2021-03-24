/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/24 15:50:45 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

t_global	g;

// Превратить список с окружением в двумерный массив
char	**env_to_args()
{
	
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

void	other_cmd()
{
	
	execve();
}

void	commands(char *cmd)
{
	if (!ft_strncmp(cmd, PWD, ft_strlen(PWD)))
		cmd_pwd();
	else if (!ft_strncmp(cmd, CD, ft_strlen(CD)))
		cd_pwd();
	else
		other_cmd();
}

int main(int argc, char *argv[], char **envp)
{
	init_env(&g.root, envp);
	g.argv = argv;
	t_list *next = g.root;
	printf("----------------------------------\n");
	commands(PWD);
	
	printf("----------------------------------\n");
	delete_list(&g.root);
}