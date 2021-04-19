#include "../include/shell.h"

void	cmd_env(char **cmd)
{
	t_list	*next;

	next = g_gl.root;
	if (arr_size(cmd) != 1)
	{
		g_gl.error_code[0] = '1';
		g_gl.error_code[1] = '2';
		g_gl.error_code[2] = '7';
		g_gl.error_code[3] = 0;
		print_error("minishell:  env: ", 0);
		print_error(cmd[1], 0);
		print_error(": No such file or directory\n", 0);
		return ;
	}
	while (next)
	{
		put_srt(next->key);
		put_srt("=");
		put_srtln(next->value);
		next = next->next;
		g_gl.error_code[0] = '0';
		g_gl.error_code[1] = 0;
	}
}
