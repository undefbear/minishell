/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/17 16:21:40 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_export_2(char *cmd)
{
	if (!find_list(g_gl.root, cmd))
	{
		if (!find_list(g_gl.export, cmd))
			add_elem(&g_gl.export, ft_strdup(cmd), ft_strdup(""));
	}
}

void	print_export(void)
{
	t_list	*next;

	next = g_gl.root;
	while (next)
	{
		put_srt("declare -x ");
		put_srt(next->key);
		put_srt("=\"");
		put_srt(next->value);
		put_srtln("\"");
		next = next->next;
	}
	next = g_gl.export;
	while (next)
	{
		printf("declare -x %s\n", next->key);
		next = next->next;
	}
}
