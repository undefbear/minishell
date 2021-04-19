#include "../include/shell.h"

int	equals(char *str1, char *str2)
{
	if (ft_strlen(str1) == ft_strlen(str2)
		&& !ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

void	change_value(t_list *root, char *key, char *value)
{
	t_list	*next;

	next = root;
	while (next)
	{
		if (equals(next->key, key))
		{
			free(next->value);
			next->value = value;
			break ;
		}
		next = next->next;
	}
}

void	add_elem(t_list **root, char *key, char *value)
{
	t_list	*tmp;
	t_list	*next;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		cmd_exit(NULL);
	ft_bzero(tmp, sizeof(t_list));
	tmp->key = key;
	tmp->next = NULL;
	tmp->value = value;
	if (*root == NULL)
		*root = tmp;
	else
	{
		next = *root;
		while (next->next)
			next = next->next;
		next->next = tmp;
	}
}

char	*find_list(t_list *root, char *key)
{
	t_list	*next;

	next = root;
	while (next)
	{
		if (equals(next->key, key))
			return (next->value);
		next = next->next;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	i = 0;
	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	while (tmp_s1[i] != '\0' && tmp_s2[i]
		!= '\0' && i < n && tmp_s1[i] == tmp_s2[i])
		i++;
	if (i == n)
		return (0);
	return (tmp_s1[i] - tmp_s2[i]);
}
