/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:54:04 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/24 15:52:29 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

//изменить значение в списке с переменными окружения по ключу
void		change_value(t_list *root, char *key, char *value)
{
	t_list *next;

	next = root;
	while (next)
	{
		if (!ft_strncmp(next->key, key, ft_strlen(key)))
		{
			free(next->value);
			next->value = value;
			break ;
		}
		next = next->next;
	}
}

// добавить элемент в список переменных окружения
void		add_elem(t_list **root, char *key, char *value)
{
	t_list *tmp;
	t_list *next;

	tmp = malloc(sizeof(t_list));
	tmp->key = key;
	tmp->next = NULL;
	tmp->value = value;	
	if (*root == NULL)
		*root = tmp;
	else
	{
		next = *root;
		while (next->next)
			next = next->next;
		next->next = tmp;		
	}
}

//найти элемент в списке переменных окружения по ключу
char		*find_list(t_list *root, char *key)
{
	t_list *next;

	next = root;
	while (next)
	{
		if (!ft_strncmp(next->key, key, ft_strlen(key)))
			return next->value;
		next = next->next;
	}
	return (NULL);
}

// просто удаление списка)
void		delete_list(t_list **root)
{
	t_list *next;

	next = *root;
	while (next)
	{
		next = (*root)->next;
		free((*root)->key);
		free((*root)->value);
		free(*root);
		*root = next;
	}
}

// функция заполнения и инициализации списка переменными окружения
void		init_env(t_list **root, char **env)
{
	char **env_tmp;
	char *parse;
	
	env_tmp = env;
	while (*env_tmp)
	{
		parse = ft_strrchr(*env_tmp, '=');
		*parse = 0;
		add_elem(root, ft_strdup(*env_tmp), ft_strdup(++parse));
		env_tmp++;
	}
}
