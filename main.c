/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/23 14:48:40 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

void	cmd_pwd(char *env)
{
	write(0, find(env, "PWD"), ft_strlen(find(env, "PWD")));
	write(0, "\n", 1);
}

void	cd_pwd(char *env)
{
	write(0, find(env, "PWD"), ft_strlen(find(env, "PWD")));
	write(0, "\n", 1);
}

void	commands(char *env, char *cmd)
{
	if (!ft_strncmp(cmd, PWD, ft_strlen(PWD)))
		cmd_pwd(env);
	else if (!ft_strncmp(cmd, CD, ft_strlen(CD)))
		cd_pwd(env);
}

int main(int argc, char *argv[], char **envp)
{
	char **tmp = envp;
	t_list *root;

	init_env(&root, envp);
	t_list *next = root;
	while (next)
	{
		printf("key = %s\t\t\tvalue = %s\n", next->key, next->value);
		next = next->next;
	}
	printf("----------------------------------\n");
	commands(root, PWD);
	
	printf("----------------------------------\n");
	delete_list(&root);
}