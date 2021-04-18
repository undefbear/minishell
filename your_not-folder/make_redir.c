/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:22:15 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/18 17:10:34 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static int	sintax_error(int *f, char **aos, int *z, char **name)
{
	*f = 0;
	if (aos[++(*z)])
		*name = create_file(aos[*z], *f);
	else
	{
		write(2, "minishell:  syntax error near unexpected token `newline'\n",
			57);
		g_gl.error_code[0] = '2';
		g_gl.error_code[1] = '5';
		g_gl.error_code[2] = '8';
		g_gl.error_code[3] = 0;
		return (1);
	}
	return (0);
}

static void	make_redirection_while(char **aos, int *f, char ***res, int *z)
{
	while (aos[++(*z)])
	{
		if (!z && !equals(aos[*z], ">")
			&& !equals(aos[*z], "<") && !equals(aos[*z], ">>"))
			*res = ft_realloc(*res, aos[*z]);
		else if (aos[*z][0] == '>' && aos[*z][1] == '>')
		{
			if (sintax_error(f, aos, z, &g_gl.nameright))
				return ;
		}
		else if (aos[*z][0] == '>')
		{
			if (sintax_error(f, aos, z, &g_gl.nameright))
				return ;
			*f = 1;
		}
		else if (aos[*z][0] == '<')
		{
			if (sintax_error(f, aos, z, &g_gl.nameleft))
				return ;
			*f = 1;
		}
		else
			*res = ft_realloc(*res, aos[*z]);
	}
}

void	make_redirection(char **aos)
{
	int		z;
	char	**res;
	int		f;

	z = -1;
	g_gl.nameleft = NULL;
	g_gl.nameright = NULL;
	res = NULL;
	make_redirection_while(aos, &f, &res, &z);
	redir_func(res, g_gl.nameright, g_gl.nameleft, f);
	g_gl.sh.flagar = 0;
}
