/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:54:04 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/25 17:13:59 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int			equals(char *str1, char *str2)
{
	if (ft_strlen(str1) == ft_strlen(str2) &&
		!ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

//изменить значение в списке с переменными окружения по ключу
void		change_value(t_list *root, char *key, char *value)
{
	t_list *next;

	next = root;
	while (next)
	{
		if (equals(next->key, key))
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
		if (equals(next->key, key))
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
// количество элементов в списке
int			list_count(t_list *root)
{
	int i;
	t_list *next;

	i = 0;
	next = root;
	while (next)
	{
		i++;
		next = next->next;
	}
	return (i);
}

// удаление элемента в списке по ключу
void	remove_elem(t_list **root, char *key)
{
	t_list *next;
	t_list *prev;
	
	next = *root;
	if (!next->next && equals(key, next->key))
	{
		free(next->key);
		free(next->value);
		free(next);
		*root = NULL;
		return ;
	}
	while (next)
	{
		if (equals(key, next->key))
		{
			prev->next = next->next;
			free(next->key);
			free(next->value);
			free(next);
			return ;
		}
		prev = next;
		next = next->next;
	}
}