/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:55:24 by ealexa            #+#    #+#             */
/*   Updated: 2021/04/12 16:57:56 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static char		*ft_strchr_comm(const char *s, int c)
{
    char sb;

    sb = (char)c;
    while (*s)
    {
        if (*s == sb && *(s - 1) != 0 && *(s - 1) == ' ')
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (0);
}


static char **check_comment(char **cmd)
{
    char *res;
    char *tmp;
    int i;
    char **strs;

    i = -1;
    res = NULL;
    while(cmd[++i])
    {
        tmp = res;
        res = ft_strjoin(res, cmd[i]);
        free(tmp);
        tmp = res;
        res = ft_strjoin(res, " ");
        free(tmp);
    }
    tmp = ft_strchr_comm(res, '#');
    if (tmp)
        *tmp = 0;
    strs = ft_split(res, ' ');
    free(res);
    return (strs);
}

static char **check_bred(char **cmd)
{
    int i;
    int j;
    char **new_cmd;

    cmd = check_comment(cmd);
    i = -1;
    j = -1;
    while(cmd[++i])
    {
        if (cmd[i][0] == '=')
            break ;
        if (!ft_strchr(cmd[i], '='))
            break ;
    }
    new_cmd = malloc(sizeof(char *) * (arr_size(cmd) - i + 1));
    if (!new_cmd)
        cmd_exit(NULL);
    ft_bzero(new_cmd, sizeof(char *) * (arr_size(cmd) - i + 1));
    while (cmd[++j + i])
        new_cmd[j] = ft_strdup(cmd[j + i]);
    new_cmd[j] = NULL;
    ft_split_free(cmd);
    return (new_cmd);
}

void	commands(char **cmd)
{
    char **new_cmd;

    new_cmd = check_bred(cmd);
    if (arr_size(new_cmd))
	{
        g.cmd = new_cmd[0];
		g.error_code[0] = '0';
		g.error_code[1] = 0;
		if (equals(PWD, new_cmd[0]))
			cmd_pwd();
		else if (equals(CD, new_cmd[0]))
			cmd_cd(new_cmd);
		else if (equals(EXPORT, new_cmd[0]))
			cmd_export(new_cmd);
		else if (equals(ENV, new_cmd[0]))
			cmd_env(new_cmd);
		else if (equals(UNSET, new_cmd[0]))
			cmd_unset(new_cmd);
		else if (equals(_ECHO, new_cmd[0]))
			cmd_echo(new_cmd);
		else if (equals(EXIT, new_cmd[0]))
			cmd_exit(new_cmd);
		else if (equals(AUTH, new_cmd[0]))
			cmd_auth();
		else
			other_cmd(new_cmd);
	}
    ft_split_free(new_cmd);
}
