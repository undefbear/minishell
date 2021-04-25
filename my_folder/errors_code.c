#include "../include/shell.h"

void	print_error(char *cmd, int f)
{
	write(2, cmd, ft_strlen(cmd));
	if (f)
		write(2, "\n", 1);
}

void	err_code127(void)
{
	g_gl.error_code[0] = '1';
	g_gl.error_code[1] = '2';
	g_gl.error_code[2] = '7';
	g_gl.error_code[3] = 0;
}

void	err_code258(void)
{
	g_gl.error_code[0] = '2';
	g_gl.error_code[1] = '5';
	g_gl.error_code[2] = '8';
	g_gl.error_code[3] = 0;
}

void	err_code1(void)
{
	g_gl.error_code[0] = '1';
	g_gl.error_code[1] = 0;
}
