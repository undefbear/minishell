/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/31 14:08:56 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_export_2(char *cmd)
{
	if (!find_list(g.root, cmd))
	{
		if (!find_list(g.export, cmd))
			add_elem(&g.export, ft_strdup(cmd), ft_strdup(""));
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
	g.error_code[0] = '1';
	g.error_code[1] = 0;
	free(key);
	free(value);
}

static int	is_str_valid(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!ft_isalpha(str[i]) && str[i] != '_')
			{
				g.error_code[0] = '1';
				g.error_code[1] = 0;
				printf("minishell: export: `%s': not a valid identifier\n", str);
				return (0);	
			}
		}
		else
		{
			if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_' || str[i] == '=' || str[i] == '/'))
			{
				g.error_code[0] = '1';
				g.error_code[1] = 0;
				printf("minishell: export: `%s': not a valid identifier\n", str);
				return (0);				
			}
		}
	}
	return (1);
}

void	cmd_export(char **cmd)
{
	int		i;
	char	*key;
	char	*value;
	char	*f;
	char	*cpy;

	i = 0;
	g.error_code[0] = '0';
	g.error_code[1] = 0;
	if (arr_size(cmd) == 1)
		print_export();
	else
	{
		while (cmd[++i])
		{
			cpy = ft_strdup(cmd[i]);
			if (ft_strlen(cpy) == 1 && cpy[0] == '_')
			{
				free(cpy);
				continue ;
			}
			if (is_str_valid(cpy))
			{
				if ((f = ft_first_strrchr(cpy, '=')))
				{
					*f = 0;
					key = ft_strdup(cpy);
					value = ft_strdup(++f);
					if (find_list(g.export, key))
						remove_elem(&g.export, key);
					if (find_list(g.root, key))
					{
						change_value(g.root, key, value);
						free(key);
					}
					else
						add_elem(&g.root, key, value);

				}
				else
					cmd_export_2(cpy);				
			}
			free(cpy);
		}
	}
}
