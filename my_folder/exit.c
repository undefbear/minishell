/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:09:01 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/02 15:17:22 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static	void	free_all()
{
	ft_split_free(g.sh.args_of_shell);
	free(g.line);
	free(g.sh.evkey);
	delete_list(&g.root);
	delete_list(&g.export);
	delete_hist(&g.head, &g.tail);
}

static int		check_param(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) || ft_strlen(str) >= 20)
		{
			return (255);
		}
	}
	return (0);
}

void	cmd_exit(char **cmd)
{
	unsigned char exit_code;

	if (!cmd)
    {
	    free_all();
        printf("minishell:  jadniy malloc :,(\n");
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
	{
		if (!check_param(cmd[1]))
		{
			g.error_code[0] = '1';
			g.error_code[1] = 0;
			printf("exit\n");
			printf("minishell:  exit: too many arguments\n");	
		}
		else
		{
			printf("exit\n");
			printf("minishell:  exit: %s: numeric argument required\n", cmd[1]);
			free_all();
			exit(255);
		}
	}
	else
	{
		exit_code = check_param(cmd[1]);
		if (exit_code)
		{
			printf("exit\n");
			printf("minishell:  exit: %s: numeric argument required\n", cmd[1]);
			free_all();
			exit(exit_code);
		}
		exit_code = ft_atoi(cmd[1]);
		printf("exit\n");
		free_all();
		exit(exit_code);
	}
}
