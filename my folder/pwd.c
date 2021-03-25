/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:23:54 by ealexa            #+#    #+#             */
/*   Updated: 2021/03/25 14:24:15 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	cmd_pwd(char **cmd)
{
	if (arr_size(cmd) != 1)
	{
		put_srtln("pwd: too many arguments");
		return ;
	}
	if (find_list(g.root, "PWD"))
		put_srtln(find_list(g.root, "PWD"));
	else
		put_srtln("я пока хз как это должно работать");
}
