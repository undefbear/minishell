/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:01:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/18 11:05:15 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static size_t	sp_size(char const *s, char c)
{
	size_t	start;
	size_t	i;
	size_t	j;

	start = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c && (start - i) > 1)
		{
			j++;
			start = i + 1;
		}
		else if (s[i] == c)
			start = i + 1;
		i++;
	}
	j++;
	return (j);
}

static char	*add_word(size_t start, size_t end, char const *s)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 1));
	if (res != NULL)
	{
		while (start != end)
			res[i++] = s[start++];
		res[i] = '\0';
	}
	return (res);
}

static char	*ft_split_2(char *s, char c, char **res)
{
	size_t	i;
	size_t	j;
	size_t	start;

	start = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c && (start - i) > 1)
		{
			res[j] = add_word(start, i, s);
			if (res[j++] == NULL)
				return (ft_split_free(res));
			start = i + 1;
		}
		else if (s[i] == c)
			start = i + 1;
		i++;
	}
	if (start != i)
		res[j++] = add_word(start, i, s);
	res[j] = 0;
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (sp_size(s, c) + 1));
	if (res != NULL)
		ft_split_2(s, c, res);
	return (res);
}
