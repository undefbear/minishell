#include "../include/shell.h"

void	delete_list(t_list **root)
{
	t_list	*next;

	next = *root;
	while (next)
	{
		next = (*root)->next;
		free((*root)->key);
		free((*root)->value);
		free(*root);
		*root = next;
	}
	*root = NULL;
}

void	init_env(t_list **root, char **env)
{
	char	**env_tmp;
	char	*parse;

	env_tmp = env;
	while (*env_tmp)
	{
		parse = ft_strrchr(*env_tmp, '=');
		*parse = 0;
		if (!equals(*env_tmp, "OLDPWD"))
			add_elem(root, ft_strdup(*env_tmp), ft_strdup(++parse));
		env_tmp++;
	}
}

int	list_count(t_list *root)
{
	int		i;
	t_list	*next;

	i = 0;
	next = root;
	while (next)
	{
		i++;
		next = next->next;
	}
	return (i);
}

static int	remove_elem_2 (char *key, t_list *next, t_list *prev, t_list **root)
{
	if (equals(key, next->key))
	{
		if (next == *root)
			*root = next->next;
		else
			prev->next = next->next;
		free(next->key);
		free(next->value);
		free(next);
		return (1);
	}
	return (0);
}

void	remove_elem(t_list **root, char *key)
{
	t_list	*next;
	t_list	*prev;

	next = *root;
	if (next)
	{
		if (!next->next && equals(key, next->key))
		{
			free(next->key);
			free(next->value);
			free(next);
			*root = NULL;
			return ;
		}
		while (next)
		{
			if (remove_elem_2(key, next, prev, root))
				return ;
			prev = next;
			next = next->next;
		}
	}
}
