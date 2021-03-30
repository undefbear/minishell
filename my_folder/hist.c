/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:44:58 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/30 16:54:44 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void handle_sigint(int sig)
{
	sig = 0;
    // printf("\nminishell:  ");
}
void	signals()
{
	g.head = NULL;
	g.tail = NULL;
	hist_add(&g.head, &g.tail, ft_strdup(""));
	signal(SIGINT, handle_sigint);
}

void	hist_add(t_hist **head, t_hist **tail,char *value)
{
	t_hist *elem;

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
