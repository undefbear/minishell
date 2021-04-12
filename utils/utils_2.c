/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:39:35 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 17:59:27 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	env_to_args_2(t_list *next, char **strs, int *i)
{
	int		j;

	j = -1;
	strs[*i] = malloc(sizeof(char) * (ft_strlen(next->key)
				 + ft_strlen(next->value) + 3));
	while (++j < ft_strlen(next->key) + ft_strlen(next->value) + 2)
	{
		if (j < ft_strlen(next->key))
			strs[*i][j] = next->key[j];
		else if (j == ft_strlen(next->key))
			strs[*i][j] = '=';
		else
			strs[*i][j] = next->value[j - ft_strlen(next->key) - 1];
	}
	strs[(*i)++][j] = 0;
}

char	**env_to_args(void)
{
	char	**strs;
	t_list	*next;
	int		i;

	i = 0;
	strs = malloc(sizeof(char *) * (list_count(g.root) + 1));
	next = g.root;
	while (next)
	{
		env_to_args_2(next, strs, &i);
		next = next->next;
	}
	strs[i] = 0;
	return (strs);
}

static size_t	ft_strjoin2(size_t size1, char *s1, char *res)
{
	size_t	i;

	i = 0;
	while (i < size1)
	{
		res[i] = s1[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		size1;
	int		size2;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (size1 + size2 + 1));
	if (res != NULL)
	{
		i = ft_strjoin2(size1, s1, res);
		while (i < size1 + size2)
		{
			res[i] = s2[i - size1];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
