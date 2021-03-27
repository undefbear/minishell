/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/27 15:30:29 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_exit(char **cmd)
{
	if (arr_size(cmd) == 1)
	{
		delete_list(&g.root);
		delete_list(&g.export);
		exit(0);
	}
	else if (arr_size(cmd) > 2)
	{
		g.error_code = 1;
		printf("minishell: exit: too many arguments\n");
	}
	else
	{
		g.error_code = ft_atoi(cmd[1]);
		delete_list(&g.root);
		delete_list(&g.export);
		exit(g.error_code);	
	}
}

void	commands(char **cmd)
{
	if (equals(PWD, cmd[0]))
		cmd_pwd(cmd);
	else if (equals(CD, cmd[0]))
		cmd_cd(cmd);
	else if (equals(EXPORT, cmd[0]))
		cmd_export(cmd);
	else if (equals(ENV, cmd[0]))
		cmd_env(cmd);
	else if (equals(UNSET, cmd[0]))
		cmd_unset(cmd);
	else if (equals(ECHO, cmd[0]))
		cmd_echo(cmd);
	else if (equals(EXIT, cmd[0]))
		cmd_exit(cmd);
	else
		other_cmd(cmd);
}

//int main(int argc, char *argv[], char **envp)
//{
//	if (!argc)
//		return 0;
//	ft_bzero(&g, sizeof(t_global));
//	// char *ls1[4] = {
//	// 	"ls",
//	// 	0
//	// };
//	// char *ls2[4] = {
//	// 	"ls",
//	// 	"-la",
//	// 	0
//	// };
//	// char *ls3[4] = {
//	// 	"ls",
//	// 	"-la",
//	// 	"-asd",
//	// 	0
//	// };
//
//
//	// char *pwd1[4] = {
//		// "pwd",
//		// 0
//	// };
//	// char *pwd2[4] = {
//	// 	"pwd",
//	// 	"213213",
//	// 	0
//	// };
//
//
//
//	// char *env[2] = {
//	// 	"env",
//	// 	0
//	// };
//
//
//
//	// char *exp1[4] = {
//	// 	"export",
//	// 	"ASD=SAD",
//	// 	0
//	// };
//
//	// char *exp2[4] = {
//	// 	"export",
//	// 	"ASD=A",
//	// 	0
//	// };
//	// char *exp3[4] = {
//	// 	"export",
//	// 	"afsdzghf",
//	// 	"asdsad",
//	// 	0
//	// };
//	// char *exp4[4] = {
//	// 	"export",
//	// 	"TER=",
//	// 	"asdsad",
//	// 	0
//	// };
//	// char *exp5[4] = {
//	// 	"export",
//	// 	0
//	// };
//
//	// char *unset1[3] = {
//	// 	"unset",
//	// 	"PATH",
//	// 	0
//	// };
//	// char *unset2[3] = {
//	// 	"unset",
//	// 	"ASD",
//	// 	0
//	// };
//	// char *unset3[3] = {
//	// 	"unset",
//	// 	"asdsad",
//	// 	0
//	// };
//	// char *unset4[3] = {
//	// 	"unset",
//	// 	"TER",
//	// 	0
//	// };
//	// char *unset5[5] = {
//	// 	"unset",
//	// 	"123",
//	// 	"asdf",
//	// 	"=TER",
//	// 	0
//	// };
//	// char *unset6[9] = {
//	// 	"unset",
//	// 	"1",
//	// 	"2",
//	// 	"a",
//	// 	"123sd1",
//	// 	"1ssssss1",
//	// 	"2",
//	// 	"a",
//	// 	0
//	// };
//
//	// char *echo1[4] = {
//	// 	"echo",
//	// 	"echo123123",
//	// 	"sadfsadf12-sdf+gsr",
//	// 	0
//	// };
//	// char *echo2[5] = {
//	// 	"echo",
//	// 	"-n",
//	// 	"-",
//	// 	"sadfsadf12-sdf+gsr",
//	// 	0
//	// };
//	// char *echo3[4] = {
//	// 	"echo",
//	// 	"sadfsadf12-sdf+gsr",
//	// 	"-n",
//	// 	0
//	// };
//	// char *echo4[5] = {
//	// 	"echo",
//	// 	"-",
//	// 	"-n",
//	// 	"21easd",
//	// 	0
//	// };
//
//	// char *cd1[2] = {
//	// 	"cd",
//	// 	0
//	// };
//	// char *cd2[3] = {
//	// 	"cd",
//	// 	"..",
//	// 	0
//	// };
//	// char *cd3[3] = {
//	// 	"cd",
//	// 	"../asdasd",
//	// 	0
//	// };
//
//
//
//	init_env(&g.root, envp);
//	g.argv = argv;
//
//
//
//
//
//
//
//	// printf("--------------   ls1   --------------\n");
//	// commands(ls1);
//	// printf("----------------------------------\n");
//	// printf("--------------   ls2   --------------\n");
//	// commands(ls2);
//	// printf("----------------------------------\n");
//	// printf("--------------   ls3   --------------\n");
//	// commands(ls3);
//	// printf("----------------------------------\n");
//
//
//	// printf("--------------   pwd1   --------------\n");
//	// commands(pwd1);
//	// printf("----------------------------------\n");
//	// printf("--------------   pwd2   --------------\n");
//	// commands(pwd2);
//	// printf("----------------------------------\n");
//
//
//	// commands(env);
//	// printf("--------------   export1   --------------\n");
//	// commands(exp1);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   export2   --------------\n");
//	// commands(exp2);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   export3   --------------\n");
//	// commands(exp3);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   export4   --------------\n");
//	// commands(exp4);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   export5   --------------\n");
//	// commands(exp5);
//	// printf("----------------------------------\n");
//
//
//
//
//	// printf("--------------   unset1   --------------\n");
//	// commands(unset1);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   unset2   --------------\n");
//	// commands(unset2);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   unset3   --------------\n");
//	// commands(unset3);
//	// commands(env);
//	// printf("----------------------------------\n");
//	// printf("--------------   unset4   --------------\n");
//	// commands(unset4);
//	// commands(exp5);
//	// printf("----------------------------------\n");
//	// printf("--------------   unset5   --------------\n");
//	// commands(unset5);
//	// printf("----------------------------------\n");
//	// printf("--------------   unset6   --------------\n");
//	// commands(unset6);
//	// printf("----------------------------------\n");
//
//
//
//	// printf("--------------   echo1   --------------\n");
//	// commands(echo1);
//	// printf("----------------------------------\n");
//	// printf("--------------   echo2   --------------\n");
//	// commands(echo2);
//	// printf("----------------------------------\n");
//	// printf("--------------   echo3   --------------\n");
//	// commands(echo3);
//	// printf("----------------------------------\n");
//	// printf("--------------   echo4   --------------\n");
//	// commands(echo4);
//	// printf("----------------------------------\n");
//
//
//
//	// printf("--------------   echo1   --------------\n");
//	// commands(echo1);
//	// printf("----------------------------------\n");
//	// printf("--------------   echo2   --------------\n");
//	// commands(echo2);
//	// printf("----------------------------------\n");
//	// printf("--------------   echo3   --------------\n");
//	// commands(echo3);
//	// printf("----------------------------------\n");
//	// printf("--------------   echo4   --------------\n");
//	// commands(echo4);
//	// printf("----------------------------------\n");
//
//
//	char *other1[3] = {
//		"ls",
//		"asdasd",
//		0
//	};
//	char *other2[3] = {
//		"ls",
//		0
//	};
//	char *other3[3] = {
//		".:::",
//		"../asdasd",
//		0
//	};
//	char *other4[3] = {
//		"lasdfafs",
//		0
//	};
//	char *other5[3] = {
//		"/bin/ls",
//		0
//	};
//	char *other6[3] = {
//		"/bin/ls",
//		"lasdfafs",
//		0
//	};
//
//
//
//	printf("--------------   .:::   --------------\n");
//	commands(other3);
//	printf("----------------------------------\n");
//
//	printf("--------------   ./lasdfafs   --------------\n");
//	commands(other4);
//	printf("----------------------------------\n");
//	printf("--------------   ls   --------------\n");
//	commands(other2);
//	printf("----------------------------------\n");
//
//	printf("%d\n", g.error_code);
//
//	printf("--------------   ls asdasd  --------------\n");
//	commands(other1);
//	printf("----------------------------------\n");
//	printf("%d\n", g.error_code);
//
//
//
//	printf("--------------   /bin/ls   --------------\n");
//	commands(other5);
//	printf("----------------------------------\n");
//	printf("%d\n", g.error_code);
//	printf("--------------   /bin/ls asdasd  --------------\n");
//	commands(other6);
//	printf("----------------------------------\n");
//	printf("%d\n", g.error_code);
//
//
//
//	char *unset1[3] = {
//		"unset",
//		0
//	};
//	char *unset2[3] = {
//		"unset",
//		"=PATH",
//		0
//	};
//	char *unset3[3] = {
//		"unset",
//		"asd=sad",
//		0
//	};
//
//	printf("--------------   unset   --------------\n");
//	commands(unset1);
//	printf("%d\n", g.error_code);
//	printf("----------------------------------\n");
//	printf("--------------   unset =PATH   --------------\n");
//	commands(unset2);
//	printf("%d\n", g.error_code);
//	printf("----------------------------------\n");
//	printf("--------------   unset3   --------------\n");
//	commands(unset3);
//	printf("%d\n", g.error_code);
//	printf("----------------------------------\n");
//	printf("--------------   unset   --------------\n");
//	commands(unset1);
//	printf("%d\n", g.error_code);
//	printf("----------------------------------\n");
//
//	delete_list(&g.root);
//	delete_list(&g.export);
//	return (0);
//}
