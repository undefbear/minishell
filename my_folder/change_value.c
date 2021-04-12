/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 16:50:43 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	ft_change(char **res, char *value, int j, char *tmp)
{
	int	i;

	i = 0;
	while (value && value[i])
	{
		if ((int)ft_isprint(value[i]))
			tmp[j + i] = value[i];
		else
			j--;
		i++;
	}
	tmp[j + i] = 0;
	free(*res);
	*res = tmp;
}

static void	ft_change_value_3(char **res, char *value, int flag, int col)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
	ft_bzero(tmp, sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
	i = 0;
	j = 0;
	while (*res && (*res)[i])
	{
		if ((int)ft_isprint((*res)[i]))
			tmp[i - j] = (*res)[i];
		else
			j++;
		i++;
	}
	j = i - j;
	ft_change(res, value, j, tmp);
}

static void	ft_change_value_2(char **res, char *value, int flag, int col)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp = malloc(sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
	ft_bzero(tmp, sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
	while (++i < ft_strlen(*res) - col)
		tmp[i] = (*res)[i];
	while (++j < ft_strlen(value))
		tmp[i + j] = value[j];
	i -= 1;
	while (++i < ft_strlen(*res))
		tmp[i + j] = (*res)[i];
	tmp[i + j] = 0;
	free(*res);
	*res = tmp;
}

void	ft_change_value(char **res, char *value, int flag, int col)
{
	int		i;
	int		j;
	char	*tmp;

	if (flag && !col)
		ft_change_value_3(res, value, flag, col);
	else if (flag)
		ft_change_value_2(res, value, flag, col);
	else
	{
		free(*res);
		*res = ft_strdup(value);
	}
}
