#include "../include/shell.h"

void	cmd_export_2(char *cmd)
{
	if (!find_list(g_gl.root, cmd))
	{
		if (!find_list(g_gl.export, cmd))
			add_elem(&g_gl.export, ft_strdup(cmd), ft_strdup(""));
	}
}

void	print_export(void)
{
	t_list	*next;

	next = g_gl.root;
	while (next)
	{
		put_srt("declare -x ");
		put_srt(next->key);
		put_srt("=\"");
		put_srt(next->value);
		put_srtln("\"");
		next = next->next;
	}
	next = g_gl.export;
	while (next)
	{
		printf("declare -x %s\n", next->key);
		next = next->next;
	}
}
