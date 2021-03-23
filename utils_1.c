/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:18:33 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/23 14:47:50 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	*tmp_s;

	tmp_s = (char*)s;
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

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);	
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*res;

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	i = 0;
	tmp_s1 = (unsigned char*)s1;
	tmp_s2 = (unsigned char*)s2;
	while (tmp_s1[i] != '\0' && tmp_s2[i]
	!= '\0' && i < n && tmp_s1[i] == tmp_s2[i])
		i++;
	if (i == n)
		return (0);
	return (tmp_s1[i] - tmp_s2[i]);
}
