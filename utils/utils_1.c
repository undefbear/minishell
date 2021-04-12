/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:18:33 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 17:31:01 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*ft_first_strrchr(const char *s, int c)
{
	char	*res;
	char	*tmp_s;

	tmp_s = (char *)s;
	res = 0;
	while (*tmp_s)
	{
		if (*tmp_s == (char)c)
		{
			res = tmp_s;
			return (res);
		}
		tmp_s++;
	}
	if (*tmp_s == (char)c)
		res = tmp_s;
	return (res);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	*tmp_s;

	tmp_s = (char *)s;
	res = 0;
	while (*tmp_s)
	{
		if (*tmp_s == (char)c)
			res = tmp_s;
		tmp_s++;
	}
	if (*tmp_s == (char)c)
		res = tmp_s;
	return (res);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*res;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (res != NULL)
	{
		i = 0;
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}
