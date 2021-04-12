/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:09:01 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 15:23:36 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static	void	free_all(void)
{
	ft_split_free(g.sh.args_of_shell);
	free(g.line);
	free(g.sh.evkey);
	delete_list(&g.root);
	delete_list(&g.export);
	delete_hist(&g.head, &g.tail);
}

static int	check_param(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) || ft_strlen(str) >= 20)
			return (255);
	}
	return (0);
}

static void	cmd_exit_2(char **cmd)
{
	if (!check_param(cmd[1]))
	{
		g.error_code[0] = '1';
		g.error_code[1] = 0;
		printf("exit\n");
		print_error("minishell:  exit: too many arguments\n", 0);
	}
	else
	{
		printf("exit\n");
		print_error("minishell:  exit: ", 0);
		print_error(cmd[1], 0);
		print_error(": numeric argument required\n", 0);
		free_all();
		exit(255);
	}
}

static void	cmd_exit_3(char **cmd)
{
	unsigned char	exit_code;

	exit_code = check_param(cmd[1]);
	if (exit_code)
	{
		printf("exit\n");
		print_error("minishell:  exit: ", 0);
		print_error(cmd[1], 0);
		print_error(": numeric argument required\n", 0);
		free_all();
		exit(exit_code);
	}
	exit_code = ft_atoi(cmd[1]);
	printf("exit\n");
	free_all();
	exit(exit_code);
}

void	cmd_exit(char **cmd)
{
	if (!cmd)
	{
		free_all();
		print_error("minishell:  jadniy malloc :,(\n", 0);
		exit(127);
	}
	if (arr_size(cmd) == 1)
	{
		if (g.flag)
		{
			write(0, "exit\n", 5);
			free_all();
			exit(127);
		}
		free_all();
		printf("exit\n");
		exit(0);
	}
	else if (arr_size(cmd) > 2)
		cmd_exit_2(cmd);
	else
		cmd_exit_3(cmd);
}
