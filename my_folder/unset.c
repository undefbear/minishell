/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:04:23 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 17:04:47 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	is_str_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!(!ft_isalpha(str[i]) || str[i] != '_'))
				return (0);
		}
		else
			if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
				return (0);
	}
	return (1);
}

void	cmd_unset(char **cmd)
{
	int	i;

	i = 0;
	if (arr_size(cmd) == 1)
		return ;
	while (cmd[++i])
	{
		if (ft_strlen(cmd[i]) == 1 && cmd[i][0] == '_')
			continue ;
		if (is_str_valid(cmd[i]))
		{
			remove_elem(&g.root, cmd[i]);
			remove_elem(&g.export, cmd[i]);
		}
		else
		{
			g.error_code[0] = '1';
			g.error_code[1] = 0;
			print_error("minishell:  unset: `", 0);
			print_error(cmd[i], 0);
			print_error("': not a valid identifier", 1);
		}
	}
}
