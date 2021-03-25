/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/25 18:27:27 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_env(char **cmd)
{
	t_list *next;

	next = g.root;
	if (arr_size(cmd) != 1)
	{
		put_srtln("alot of arguments for env");
		return ;
	}
	while (next)
	{
		put_srt(next->key);
		put_srt("=");
		put_srtln(next->value);
		next = next->next;
	}
}

// void	cmd_cd(char **cmd)
// {
// 	write(0, find_list(g.root, "PWD"), ft_strlen(find_list(g.root, "PWD")));
// 	write(0, "\n", 1);
// }

// void	unset(char **cmd)
// {
// 	int i;

// 	i = 0;
// 	while (cmd[++i])
// 	{
// 		if (ft_isalpha(cmd[i][0]))
// 		{
// 			remove_elem(&g.root, cmd[i]);
// 		}
// 	}
// }

void	commands(char **cmd)
{

	if (equals(PWD, cmd[0]))
		cmd_pwd(cmd);
	// else if (!ft_strncmp(cmd[0], CD, ft_strlen(CD)))
	// 	cmd_cd(cmd);
	else if (equals(EXPORT, cmd[0]))
		cmd_export(cmd);
	else if (equals(ENV, cmd[0]))
		cmd_env(cmd);
	// else if (equals(UNSET, cmd[0]))
	// 	unset(cmd);
	else
		other_cmd_without_slesh(cmd);
}

int main(int argc, char *argv[], char **envp)
{
	if (!argc)
		return 0;
	char *ls1[4] = {
		"ls",
		0
	};
	char *ls2[4] = {
		"ls",
		"-la",
		0
	};
	char *ls3[4] = {
		"ls",
		"-la",
		"-asd",
		0
	};


	char *pwd1[4] = {
		"pwd",
		0
	};
	char *pwd2[4] = {
		"pwd",
		"213213",
		0
	};

	char *env[2] = {
		"env",
		0
	};
	
	char *exp1[4] = {
		"export",
		"ASD=SAD",
		0
	};

	char *exp2[4] = {
		"export",
		"ASD=A",
		0
	};
	char *exp3[4] = {
		"export",
		"TER=",
		"asdsad",
		0
	};


	char *env1[3] = {
		"env",
		"12312",
		0
	};

	// char *unset1[3] = {
	// 	"unset",
	// 	"12312",
	// 	0
	// };


	
	init_env(&g.root, envp);
	g.argv = argv;
	printf("--------------   ls1   --------------\n");
	commands(ls1);
	printf("----------------------------------\n");
	printf("--------------   ls2   --------------\n");
	commands(ls2);
	printf("----------------------------------\n");
	printf("--------------   ls3   --------------\n");
	commands(ls3);
	printf("----------------------------------\n");

	
	printf("--------------   pwd1   --------------\n");
	commands(pwd1);
	printf("----------------------------------\n");
	printf("--------------   pwd2   --------------\n");
	commands(pwd2);
	printf("----------------------------------\n");


	commands(env);
	printf("--------------   export1   --------------\n");
	commands(exp1);
	commands(env);
	printf("----------------------------------\n");
	printf("--------------   export2   --------------\n");
	commands(exp2);
	commands(env);
	printf("----------------------------------\n");
	printf("--------------   export3   --------------\n");
	commands(exp3);
	commands(env);
	printf("----------------------------------\n");



	printf("--------------   env   --------------\n");
	commands(env1);
	printf("----------------------------------\n");


	printf("--------------   unset1   --------------\n");
	commands(exp1);
	commands(env);
	printf("----------------------------------\n");
	printf("--------------   unset2   --------------\n");
	commands(exp2);
	commands(env);
	printf("----------------------------------\n");
	printf("--------------   unset3   --------------\n");
	commands(exp3);
	commands(env);
	printf("----------------------------------\n");
	delete_list(&g.root);
	return (0);
}
