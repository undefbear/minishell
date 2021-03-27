/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/27 20:02:30 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_export_2(char *cmd)
{
	if (ft_isalpha(cmd[0]))
	{
		if (!find_list(g.root, cmd))
		{
			if (!find_list(g.export, cmd))
				add_elem(&g.export, ft_strdup(cmd), ft_strdup(""));
			else
			{
				add_elem(&g.root, ft_strdup(cmd), ft_strdup(""));
				remove_elem(&g.export, cmd);
			}
		}
	}
	else
	{
		g.error_code = 1;
		printf("minishell: no matches found: %s\n", cmd);		
	}
}

void	print_export()
{
	t_list *next;

	next = g.root;
	while (next)
	{
		put_srt("declare -x ");
		put_srt(next->key);
		put_srt("=\"");
		put_srt(next->value);
		put_srtln("\"");
		next = next->next;
	}
	next = g.export;
	while (next)
	{
		printf("declare -x %s\n", next->key);
		next = next->next;
	}
}

void	cmd_export_err(char *cpy, char *key, char *value)
{
	if (cpy[0] == '=' && !ft_strlen(cpy))
		printf("minishell: bad assignment\n");
	else if (cpy[0] == '=')
		printf("minishell: %s not found\n", ++cpy);
	else if (cpy[0] == '*' && !ft_strlen(cpy))
		printf("minishell: export: not valid in this context: export.c\n");
	else if (cpy[0] == '*')
		printf("minishell: no matches found: %s\n", ++cpy);
	else
		printf("minishell: export: not an identifier: %s\n", cpy);	
	g.error_code = 1;
	free(key);
	free(value);
}

void	cmd_export(char **cmd)
{
	int		i;
	char	*key;
	char	*value;
	char	*f;
	char	*cpy;

	i = 0;
	g.error_code = 0;
	if (arr_size(cmd) == 1)
		print_export();
	else
	{
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
					cmd_export_err(cpy, key, value);
			}
			else
				cmd_export_2(cpy);
			free(cpy);
		}
	}
}
