#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <dirent.h>

# define PWD "pwd"
# define CD "cd"
# define EXPORT "export"
# define ENV "env"
# define UNSET "unset"
# define _ECHO "echo"
# define EXIT "exit"
# define AUTH "authors"
# define BUFF_SIZE 2000

typedef struct s_shell
{
	int					flag1;
	int					flag2;
	int					flagar;
	int					lenght;
	int					dollen;
	int					numargs;
	char				*evkey;
	char				*evvalue;
	int					valuelen;
	char				**args_of_shell;
}						t_shell;

typedef struct s_list
{
	struct s_list	*next;
	char			*key;
	char			*value;
}					t_list;

typedef struct s_hist
{
	struct s_hist	*next;
	struct s_hist	*prev;
	char			*value;
}					t_hist;

typedef struct s_global
{
	t_list				*root;
	t_list				*export;
	char				error_code[4];
	t_hist				*head;
	t_hist				*tail;
	char				**res;
	int					flag;
	t_shell				sh;
	char				*line;
	int					col;
	int					echon;
	int				 	fd_out;
	int				 	fd_in;
	int					fdp[2];
	pid_t				pid;
	int					numpipes;
	struct termios		term;
	char				*cmd;
	char				*nameright;
	char				*nameleft;
	int					flagf;
	int					flag_semi;
	int					flag_pipe;
}					t_global;

t_global	g_gl;

void			add_elem(t_list **root, char *key, char *value);
void			init_env(t_list **root, char **env);
void			delete_list(t_list **root);
char			*find_list(t_list *root, char *key);
char			*ft_strdup(const char *s1);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(char *str);
char			*ft_strrchr(const char *s, int c);
char			*ft_strchr(const char *s, int c);
int				list_count(t_list *root);
char			**env_to_args(void);
void			*ft_split_free(char **start);
char			*ft_strjoin(char *s1, char *s2);
void			put_srt(char *str);
void			put_srtln(char *str);
int				arr_size(char **strs);
void			cmd_pwd(void);
int				ft_isalpha(int c);
void			change_value(t_list *root, char *key, char *value);
char			*ft_first_strrchr(const char *s, int c);
int				equals(char *str1, char *str2);
void			cmd_export(char **cmd);
void			remove_elem(t_list **root, char *key);
void			cmd_env(char **cmd);
int				ft_isdigit(int c);
void			cmd_unset(char **cmd);
void			cmd_echo(char **cmd);
void			commands(char **cmd);
void			cmd_cd(char **cmd);
void			other_cmd(char **cmd);
void			ft_bzero(void *s, size_t n);
int				*gnl_v2(char **res);
void			hist_add(t_hist **head, t_hist **tail, char *value);
void			signals(void);
void			cmd_exit(char **cmd);
void			delete_hist(t_hist **head, t_hist **tail);
int				ft_isprint(unsigned char c);
int				ft_putchar(int c);
void			cmd_auth(void);
void			print_error(char *cmd, int f);
void			err_code127(void);
void			err_code1(void);
void			cmd_export_2(char *cmd);
void			print_export(void);
void			press_key_up(t_hist **hist, char **res, int *col);
void			press_key_down(t_hist **hist, char **res, int *col);
void			ft_change_value(char **res, char *value, int flag, int col);
void			press_key_left(char **res, int *col, int l, char str[2000]);
void			press_key_right(char **res, int *col, int l, char str[2000]);
void			press_key_delete(char **res, int *col);
void			delete_sym(char **res, int col);
void			press_enter(int *col, char **res, char str[2000], int l);
void			press_other(char str[2000], char **res, int *col);
void			press_sigint(char **res);
void			ft_change_value(char **res, char *value, int flag, int col);
int				check_slesh(char *str);
void			other_cmd_without_slesh(char **cmd);
char			*cheack_path(char *cmd);
char			*finde_new_path(char **path);
void			arg_itoa(int num);
char			*ft_strnstr(char *haystack, char *needle, int len);
int				is_str_valid_my(char *str);
int				check_slesh(char *str);
void			arg_itoa(int rv);
char			*cheack_path_2(char *cmd, char *path);
long long int	ft_atoi(const char *str);
char			**ft_realloc(char **strs, char *value);
char			*create_file(char *name, int f);
void			redir_func(char **cmd, char *nameright, char *nameleft, int f);
int				parse_shell(t_shell *sh, char *line, int i);
int				init_first_pointer(t_shell *sh);
int				init_new_pointer(t_shell *sh);
void			change_pos(t_shell *sh, char c, int *i);
void			if_find_elem(char *arg, int *i, t_shell *sh);
int				prepare_array(t_shell *sh, char *arg, int *i, char till);
void			init_shell_struct (t_shell *sh);
int				init_env_var(char *env_variable, t_shell *sh, int *z);
int				find_lenght(char *line, char till, int i);
int				find_value(t_shell *sh);
char			*init_array(t_shell *sh);
int				check_elem(t_shell *sh, char *line, int *i, int *z);
int				create_tokens (t_shell *sh, char *line, int *i, int z);
void			create_env(t_shell *sh, int *z, int *i);
void			create_word(t_shell *sh, char *line, int *i, int *z);
int				its_pipe(t_shell *sh, int f);
int				its_last_pipe(char **sh);
void			make_redirection(char **aos);
void			term_back_normal(void);
void			term_init(void);
int				is_sym_valid(int c);
void			err_code258(void);
char			*create_file(char *name, int f);
char			**ft_realloc(char **strs, char *value);

#endif