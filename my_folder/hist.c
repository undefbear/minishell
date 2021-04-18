/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:44:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/18 18:07:42 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	handle_sigquit(int sig)
{
	if (g_gl.pid && !equals(g_gl.cmd, "read"))
	{
		sig = 8;
		write(0, "Quit: 3\n", sig);
		g_gl.error_code[0] = '1';
		g_gl.error_code[1] = '3';
		g_gl.error_code[2] = '1';
		g_gl.error_code[3] = 0;
	}
}

void	handle_sigint(int sig)
{
	write(0, "\nminishell:   ", 13);
	sig = 0;
	free(*g_gl.res);
	*g_gl.res = NULL;
	err_code1();
	if (g_gl.cmd && ft_strnstr(g_gl.cmd, "cat", ft_strlen(g_gl.cmd)))
	{
		g_gl.error_code[0] = '1';
		g_gl.error_code[1] = '3';
		g_gl.error_code[2] = '0';
		g_gl.error_code[3] = 0;
	}
}

void	signals(void)
{
	g_gl.error_code[0] = '0';
	g_gl.error_code[1] = 0;
	g_gl.head = NULL;
	g_gl.tail = NULL;
	g_gl.fd_in = 0;
	g_gl.fd_out = 1;
	hist_add(&g_gl.head, &g_gl.tail, ft_strdup(""));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	delete_hist(t_hist **head, t_hist **tail)
{
	t_hist	*next;
	t_hist	*tmp;

	next = *head;
	while (next)
	{
		tmp = next;
		free(next->value);
		next = next->next;
		free(tmp);
	}
	*head = NULL;
	*tail = NULL;
}

void	hist_add(t_hist **head, t_hist **tail, char *value)
{
	t_hist	*elem;

	elem = malloc(sizeof(t_hist));
	elem->value = value;
	elem->next = NULL;
	elem->prev = NULL;
	if (!*head)
	{
		*head = elem;
		*tail = elem;
	}
	else
	{
		(*head)->prev = elem;
		elem->next = (*head);
		*head = elem;
	}
}
