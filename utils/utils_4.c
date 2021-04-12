/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:39:35 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 18:40:26 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	*ft_split_free(char **start)
{
	int	i;

	i = 0;
	while (start && start[i] != NULL)
		free(start[i++]);
	free(start);
	return (NULL);
}

void	put_srt(char *str)
{
	write(1, str, ft_strlen(str));
}

void	put_srtln(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}
