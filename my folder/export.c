/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/25 16:54:39 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_export(char **cmd)
{
	int i;
	char *key;
	char *value;
	char *f;
	char	*cpy;

	i = 0;
	while (cmd[++i])
	{
		cpy = ft_strdup(cmd[i]);
		if ((f = ft_first_strrchr(cpy, '=')))
		{
			*f = 0;
			key = ft_strdup(cpy);
			value = ft_strdup(++f);
			if (ft_isalpha(key[0]))
			{
				if (find_list(g.root, key))
				{
					change_value(g.root, key, value);
					free(key);
				}
				else
					add_elem(&g.root, key, value);
			}
			else
			{
				free(key);
				free(value);	
			}
		}
		free(cpy);
	}
}
