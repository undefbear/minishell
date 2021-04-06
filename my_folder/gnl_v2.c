#include "../include/shell.h"

int		ft_putchar(int c)
{
	return (write(0, &c, 1));
}

//void	pos_curs(int *row, int *col)
//{
//    char	pos[20];
//    int		i;
//
//    ft_bzero(pos, 20);
////    printf("\n%d\n", ft_strlen("\e[6n"));
//    write(1, "\e[6n", ft_strlen("\e[6n"));
//    i = read(1, pos, 100);
//    pos[i] = 0;
//    i = 2;
//    *row = ft_atoi(pos + i);
//    while (ft_isdigit(pos[i]))
//        i++;
//    *col = ft_atoi(pos + i + 1);
//}

//void    new_save_curs(char **res, int col)
//{
//    int co = tgetnum("co");
//    int li = tgetnum("li");
//    int i = 12;
//    int j = 0;
//    int k = (ft_strlen(*res) + 13 + g.echon) / co;
////    int k2 = (ft_strlen(*res) + 13 + g.echon) % co;
//    int r, c;
//    pos_curs(&r, &c);
////    int f = 1;
////    if ((ft_strlen(*res) + 12 + g.echon) / co && (ft_strlen(*res) + 12 + g.echon) && co > 0)
////        f = 0;
//    if (li < r + k)
//    {
//        tputs(restore_cursor, 1, ft_putchar);
//        while (j++ < k - 1)
//            tputs(cursor_up, 1, ft_putchar);
//        tputs(save_cursor, 1, ft_putchar);
//        while (i--)
//            tputs(cursor_left, 1, ft_putchar);
//        tputs(tigetstr("ed"), 1, ft_putchar);
//        write(1, "minishell:  ", 12);
//        put_srt(*res);
//    }
//}

static void	ft_change_value(char **res, char *value, int flag, int col)
{
    int         i;
    int         j;


	if (flag && !col)
	{
        char		*tmp;
        tmp = malloc(sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
        ft_bzero(tmp, sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
        i = 0;
        j = 0;

        while(*res && (*res)[i])
        {
            if ((int)ft_isprint((*res)[i]))
                tmp[i - j] = (*res)[i];
            else
                j++;
            i++;
        }
        j = i - j;
        i = 0;
        while(value && value[i])
        {
//            printf("%d\n", (int)ft_isprint(value[i]));
            if ((int)ft_isprint(value[i]))
                tmp[j + i] = value[i];
            else
                j--;
            i++;
        }
        tmp[j + i] = 0;
        free(*res);
        *res = tmp;
	}
	else if (flag)
	 {
         char		*tmp;
         int i = -1;
         int j = -1;
         tmp = malloc(sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
         ft_bzero(tmp, sizeof (char) * (ft_strlen(*res) + ft_strlen(value) + 1));
         while (++i < ft_strlen(*res) - col)
             tmp[i] = (*res)[i];
         while (++j < ft_strlen(value))
             tmp[i + j] = value[j];
         i -= 1;
         while (++i < ft_strlen(*res))
             tmp[i + j] = (*res)[i];
         tmp[i + j] = 0;
         free(*res);
         *res = tmp;
//         printf("\n%s\n", *res);
     }
	else
	{
		free(*res);
		*res = ft_strdup(value);
	}
}

static	void	delete_sym(char **res, int col)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(*res));
    ft_bzero(str, sizeof(char) * ft_strlen(*res));
    i = -1;
	if (!col)
    {
        while (++i < ft_strlen(*res) - 1)
            str[i] = (*res)[i];
        str[i] = 0;
        free(*res);
        *res = str;
    }
    else
    {
        while (++i < ft_strlen(*res) - col - 1)
            str[i] = (*res)[i];
        while (++i < ft_strlen(*res))
            str[i - 1] = (*res)[i];
        str[i - 1] = 0;
        free(*res);
        *res = str;
    }
}

void    cmd_auth()
{
    printf("--------------------------------\n");
    printf("|  semiteam: ealexa && kstout  |\n");
    printf("--------------------------------\n");
}

void		read_sym(char str[2000], char **res, t_hist	**hist, int *col)
{
	int		l;

	g.res = res;
	l = read(0, str, 2000);
	str[l] = 0;
    g.col = tgetnum("co");
//	pos_curs(&g.row, &g.col);
//	if (row == g.pos_start_row)
//        row = g.pos_start_row - 3;
//    printf("\n%d\t%d\n", g.row, g.col);
	if (equals(str, "\e[A"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (!*hist)
			*hist = g.head;
		put_srt((*hist)->value);
        ft_change_value(res, (*hist)->value, 0, *col);
		*hist = (*hist)->next;
//        new_save_curs(res, *col);
    }

	else if (equals(str, "\e[B"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		if (!*hist)
			*hist = g.tail;
		put_srt((*hist)->value);
        ft_change_value(res, (*hist)->value, 0, *col);
		*hist = (*hist)->prev;
//        new_save_curs(res, *col);
	}
	else if (equals(str, "\e[C"))
	{
	    if (!((ft_strlen(*res) + 12 + g.echon) % g.col - *col))
        {
            (*col) -= 1;
            tputs(cursor_down, 1, ft_putchar);
            tputs(cursor_right, 1, ft_putchar);
        }
		else if (*col != 0)
		{
            (*col) -= 1;
            write(0, str, l);
		}
	}
	else if (equals(str, "\e[D"))
	{
		if (*col < ft_strlen(*res))
		{
		    (*col) += 1;
			write(0, str, l);
		}
	}
	else if (equals(str, "\177"))
	{
        g.col = tgetnum("co");
//        printf("\n%d\n", g.col);
//	    printf("st_row = %d\trow = %d\twidth = %d\n", g.pos_start_row, row, g.width);
		if (ft_strlen(*res) - *col)
		{
//		    printf("\n%d\n", ft_strlen(*res) + 13 % g.col);
            if (((ft_strlen(*res) + 12 + g.echon) % g.col) - *col == 0)
            {
//                printf("\n123\n");
                tputs(cursor_left, 1, ft_putchar);
//                write(0, &(*res[ft_strlen(*res) - 2]), 1);
//                tputs(cursor_left, 1, ft_putchar);
                tputs(cursor_left, 1, ft_putchar);
                tputs(delete_character, 1, ft_putchar);
//                tputs(cursor_right, 1, ft_putchar);
//                tputs(delete_character, 1, ft_putchar);
//                write(0, &a, 2);
//                write(0, &(*res[ft_strlen(*res) - 2]), 1);
//                write(0, &(*res[ft_strlen(*res) - 3]), 1);
//                write(0, &(*res[ft_strlen(*res) - 1]), 1);
//                tputs(cursor_up, 1, ft_putchar);
                tputs(delete_character, 1, ft_putchar);
//                printf("%c", );
                write(0, *res + (ft_strlen(*res) - 2), 1);
                tputs(cursor_right, 1, ft_putchar);
                delete_sym(res, *col);
                if (*col)
                {
                    tputs(restore_cursor, 1, ft_putchar);
                    tputs(tigetstr("ed"), 1, ft_putchar);
                    put_srt(*res);
                    int i = -1;
                    while (++i < *col)
                        tputs(cursor_left, 1, ft_putchar);
                }
            }
            else
            {
                tputs(cursor_left, 1, ft_putchar);
                tputs(delete_character, 1, ft_putchar);
                delete_sym(res, *col);
                if (*col)
                {
//                    tputs(restore_cursor, 1, ft_putchar);
                    tputs(tigetstr("ed"), 1, ft_putchar);
//                    put_srt(*res);
                    int i = ft_strlen(*res) - *col - 1;
                    while (i++ < ft_strlen(*res))
                        write(0, (*res + i), 1);
                    i = -1;
                    while (++i < *col)
                        tputs(cursor_left, 1, ft_putchar);
                }
            }
//            (*res)[ft_strlen(*res) - 1] = 0;
//            printf("\nres2 = %d", ft_strlen(*res));
//            tputs(cursor_left, 1, ft_putchar);
//			tputs(delete_character, 1, ft_putchar);
//			 write(0, "\nminishell:  ", 13);
//			 put_srt(*res);
		}
	}
	else if  (equals(str, "\n"))
    {
	    int i;
	    int k;

	    if (*col)
	    {
            i = (ft_strlen(*res) + g.echon + 12 - *col) % g.col;
            k = ((ft_strlen(*res) + g.echon + 12) / g.col) - ((ft_strlen(*res) + g.echon + 12 - *col) / g.col);
            while (i-- > 0)
                tputs(cursor_right, 1, ft_putchar);
            while (k-- > 0)
                tputs(cursor_down, 1, ft_putchar);
	    }
        write(0, str, l);
    }
	else if (equals(str, "\x04"))
    {
	    if (!ft_strlen(*res))
        {
            free(*res);
            *res = ft_strdup("exit");
            g.flag = 1;
        }
    }
	else if (equals(str, "\x0c"))
    {
        tputs(restore_cursor, 1, ft_putchar);
        tputs(tigetstr("ed"), 1, ft_putchar);
        free(*res);
        res = NULL;

    }
	else
    {
        char *tmp = ft_strdup(str);
        ft_change_value(res, tmp, 1, *col);
        free(tmp);

        // if (!g.pos_l)
        if (*col)
        {
            tputs(restore_cursor, 1, ft_putchar);
            tputs(tigetstr("ed"), 1, ft_putchar);
            put_srt(*res);
            int i = -1;
            while (++i < *col)
                tputs(cursor_left, 1, ft_putchar);
        }
        else
        {
            int i = -1;
            while (str[++i])
            {
                if (ft_isprint(str[i]))
                    write(0, &str[i], 1);
            }
        }
    //        new_save_curs(res, *col);
    //        write(0, "\nminishell:  ", 13);
    //        put_srt(*res);
        // else
        // {
        // 	tputs(restore_cursor, 1, ft_putchar);
        // 	tputs(tigetstr("ed"), 1, ft_putchar);
        // 	put_srt(*res);
        // 	// write(0, *res, ft_strlen(*res));
        // 	int i;
        // 	i = g.pos_l;
        // 	while (i--)
        // 		tputs(cursor_left, 1, ft_putchar);
        // }
	}
}

int		*gnl_v2(char **res)
{
	char	str[2000];
	int		l;
	struct termios term;
	char	*name = "xterm-256color";
	int col;

    g.line_count = 1;
	col = 0;
	t_hist	*hist;
	hist = g.head;
	ft_bzero(str, sizeof(char) * 2000);
//	name = find_list(g.root, "TERM");
//	name = getenv("TERM");
	tcgetattr(0, &term);
	if (!name)
	{
		printf("cant to find TERM in env, pls add this param\n");
		return (0);
	}
    term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
    term.c_cc[VTIME] = 0;
    term.c_cc[VMIN] = 1;
//    term.c_lflag |= (ECHO | ICANON | ISIG);
//	term.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &term);
	l = tgetent(0, name);
	if (l <= 0)
	{
		printf("parm TERM is wrong or smth else\n");
		return (0);
	}
	*res = NULL;
//	printf("%d\t%d\n", g.heigth, g.pos_start_row);
	write(1, "minishell:  ", 12);
	tputs(save_cursor, 1, ft_putchar);
	read_sym(str, res, &hist, &col);
	while (!equals(str, "\n") && !g.flag)
		read_sym(str, res, &hist, &col);
	if (!*res)
		*res = ft_strdup("");
	if (ft_strlen(*res))
		hist_add(&g.head, &g.tail, ft_strdup(*res));
    tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO);
	term.c_oflag |= (ICANON);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
//	 printf("\n%s\n", *res);
	// printf("%d\n", g.asd);
	return 0;
}
