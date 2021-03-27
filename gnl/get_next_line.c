/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:21:27 by kstout            #+#    #+#             */
/*   Updated: 2020/11/06 20:21:36 by kstout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	check_tails(char **line, char **tail, char **end)
{
	char *tmp;

	if (*tail)
	{
		if ((*end = ft_strchr(*tail, '\n')))
		{
			**end = '\0';
			*line = ft_strdup(*tail);
			tmp = *tail;
			*tail = ft_strdup(++(*end));
			free(tmp);
			if (!*line || !*tail)
				return (-1);
		}
		else
		{
			*line = (*tail);
			(*tail) = NULL;
		}
	}
	else if (!*tail)
		if (!(*line = ft_strdup("")))
			return (-1);
	return (0);
}

static int	make_line(char *buff, char **line, char **end, char **tail)
{
	char		*tmp;

	if ((*end = ft_strchr(buff, '\n')))
	{
		**end = '\0';
		tmp = *tail;
		if (!(*tail = ft_strdup(++(*end))))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
	}
	tmp = *line;
	if (!(*line = ft_strjoin(*line, buff)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

static int	check_read(int fd, char **line, char **end, char **tail)
{
	char	*buff;
	int		len;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		return (-1);
	}
	while (!*end)
	{
		if (!(len = read(fd, buff, BUFFER_SIZE)))
		{
			free(buff);
			return (0);
		}
		buff[len] = '\0';
		if (make_line(buff, line, end, tail))
		{
			free(buff);
			return (-1);
		}
	}
	free(buff);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*tail;
	char		*end;

	end = 0;
	if (!line || BUFFER_SIZE < 1 || read(fd, NULL, 0))
		return (-1);
	if (check_tails(line, &tail, &end))
		return (-1);
	return (check_read(fd, line, &end, &tail));
}
