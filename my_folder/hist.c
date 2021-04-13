/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:44:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 16:59:48 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	handle_sigquit(int sig)
{
	if (g.pid && !equals(g.cmd, "read"))
	{
		sig = 8;
		write(0, "Quit: 3\n", sig);
		g.error_code[0] = '1';
		g.error_code[1] = '3';
		g.error_code[2] = '1';
		g.error_code[3] = 0;
	}
}

void	handle_sigint(int sig)
{
	write(0, "\nminishell:   ", 13);
	sig = 0;
	free(*g.res);
	*g.res = NULL;
	if (ft_strnstr(g.cmd, "cat", ft_strlen(g.cmd)))
    {
        g.error_code[0] = '1';
        g.error_code[1] = '3';
        g.error_code[2] = '0';
        g.error_code[3] =  0;
    }
}

void	signals(void)
{
	g.error_code[0] = '0';
	g.error_code[1] = 0;
	g.head = NULL;
	g.tail = NULL;
	g.fd_in = 0;
	g.fd_out = 1;
	hist_add(&g.head, &g.tail, ft_strdup(""));
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
