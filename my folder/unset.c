/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:04:23 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/26 17:08:32 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int		check_cmd_word(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]))
	{
		while (str[++i])
		{
			if (!ft_isdigit(str[i]))
				return (1);
		}
	}
	else
	{
		while (str[i])
		{
			if (!ft_isalpha(str[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

void	cmd_unset(char **cmd)
{
	int i;
	int f;

	i = -1;
	f = 0;
	if (arr_size(cmd) == 1)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (cmd[++i])
		if (cmd[i][0] == '=')
		{
			printf("zsh: %s not found\n", cmd[i]);
			return ;
		}
	i = 0;
	while (cmd[++i])
	{
		if (!check_cmd_word(cmd[i]))
		{
			remove_elem(&g.root, cmd[i]);
			remove_elem(&g.export, cmd[i]);	
		}
		else if (!(f++))
			printf("unset: %s: invalid parameter name\n", cmd[i]);
	}
}
