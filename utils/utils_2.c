/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:39:35 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/25 16:34:57 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

// Превратить список с окружением в двумерный массив (не забывай чистить с помощью ft_split_free)
char	**env_to_args()
{
	char	**strs;
	t_list	*next;
	int		i;
	int		j;

	i = 0;
	strs = malloc(sizeof(char *) * (list_count(g.root) + 1));
	next = g.root;
	while (next)
	{
		j = -1;
		strs[i] = malloc(sizeof(char) * (ft_strlen(next->key) + ft_strlen(next->value) + 3));
		while (++j < ft_strlen(next->key) + ft_strlen(next->value) + 2)
		{
			if (j < ft_strlen(next->key))
				strs[i][j] = next->key[j];
			else if (j == ft_strlen(next->key))
				strs[i][j] = '=';
			else
				strs[i][j] = next->value[j - ft_strlen(next->key) - 1];
		}
		strs[i++][j] = 0;
		next = next->next;
	}
	strs[i] = 0;
	return (strs);
}

void				*ft_split_free(char **start)
{
	int	i;

	i = 0;
	while (start[i] != NULL)
		free(start[i++]);
	free(start);
	return (NULL);
}

// лучше замени на свой джойн как будет время, так как мой крайне убогий))))
size_t	ft_strjoin2(size_t size1, const char *s1, char *res)
{
	size_t i;

	i = 0;
	while (i < size1)
	{
		res[i] = s1[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	size1;
	size_t	size2;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size1 = 0;
	size2 = 0;
	while (s1[size1])
		size1++;
	while (s2[size2])
		size2++;
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

// просто чтобы проще было писать строки)
void	put_srt(char *str)
{
	write(0, str, ft_strlen(str));
}

// строка с новой строкой)
void	put_srtln(char *str)
{
	write(0, str, ft_strlen(str));
	write(0, "\n", 1);
}

// подсчет эл-в в 2-мерном массиве
int		arr_size(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
		i++;
	return (i);	
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}
