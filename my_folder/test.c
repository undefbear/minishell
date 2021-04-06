#include "../include/shell.h"

int fds[2];

int main()
{
    fds[0] = 0;
    fds[1] = 1;
    char *line;

    get_next_line(0, &line);

}
