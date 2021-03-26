/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:21:10 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/26 16:21:26 by ealexa           ###   ########.fr       */
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
