#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PWD "pwd"
# define CD "cd"
# define CD "cd"



typedef struct 		s_list
{
	struct s_list	*next;
	char			*key;
	char			*value;
}					t_list;

// глобальная переменная, добавляй все чтом необходимо)
typedef struct 		s_global
{
	t_list			*root;
	char**			argv;

}					t_global;

void		add_elem(t_list **root, char *key, char *value);
void		init_env(t_list **root, char **env);
void		delete_list(t_list **root);
char		*find_list(t_list *root, char *key);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *str);
char		*ft_strrchr(const char *s, int c);

#endif