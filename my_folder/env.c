/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:21:10 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/30 16:47:03 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_env(char **cmd)
{
	t_list *next;

	next = g.root;
	if (arr_size(cmd) != 1)
	{
		g.error_code[0] = '1';
		g.error_code[1] = '2';
		g.error_code[2] = '7';
		g.error_code[3] = 0;
		put_srtln("minishell: alot of arguments for env");
		return ;
	}
	while (next)
	{
		put_srt(next->key);
		put_srt("=");
		put_srtln(next->value);
		next = next->next;
		g.error_code[0] = '0';
		g.error_code[1] = 0;
	}
}
