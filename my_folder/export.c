/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:54:16 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 15:39:16 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	cmd_export_err(char *cpy, char *key, char *value)
{
	if (cpy[0] == '=' && !ft_strlen(cpy))
		print_error("minishell:  bad assignment\n", 0);
	else if (cpy[0] == '=')
	{
		print_error("minishell:  ", 0);
		print_error(++cpy, 0);
		print_error(" not found\n", 0);
	}
	else if (cpy[0] == '*' && !ft_strlen(cpy))
		print_error
		("minishell:  export: not valid in this context: export.c\n", 0);
	else if (cpy[0] == '*')
	{
		print_error("minishell:  no matches found: ", 0);
		print_error(++cpy, 1);
	}
	else
	{
		print_error("minishell:  export: not an identifier: ", 0);
		print_error(cpy, 1);
	}
	g.error_code[0] = '1';
	g.error_code[1] = 0;
	free(key);
	free(value);
}

static void	error_mess(char *str)
{
	g.error_code[0] = '1';
	g.error_code[1] = 0;
	print_error("minishell:  export: `", 0);
	print_error(str, 0);
	print_error("': not a valid identifier\n", 0);
}

static int	is_str_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!ft_isalpha(str[i]) && str[i] != '_')
			{
				error_mess(str);
				return (0);
			}
		}
		else if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'
				|| str[i] == '=' || str[i] == '/'))
		{
			error_mess(str);
			return (0);
		}
	}
	return (1);
}

static void	export_2(char *cpy)
{
	char	*f;
	char	*key;
	char	*value;

	f = ft_first_strrchr(cpy, '=');
	if (f)
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

void	cmd_export(char **cmd)
{
	int		i;
	char	*cpy;

	i = 0;
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
				export_2(cpy);
			free(cpy);
		}
	}
}
