cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell
        your_not-folder/main.c
        your_not-folder/parse_shell.c
        gnl/get_next_line.c
        gnl/get_next_line_utils.c
        utils/list.c
        utils/utils_1.c
        utils/utils_2.c
        include/get_next_line.h
        include/shell.h
        my_folder/commands.c
        my_folder/pwd.c
        my_folder/other_cmd_wslesh.c
        my_folder/export.c
        my_folder/env.c
        my_folder/unset.c
        my_folder/echo.c
        my_folder/cd.c
        my_folder/exit.c
        my_folder/gnl_v2.c
        my_folder/hist.c
        your_not-folder/create_tokens.c
        your_not-folder/create_tokens_utils.c
        your_not-folder/parse_shell_utils.c
        your_not-folder/hi_pipe.c your_not-folder/make_redir.c)

target_link_libraries(minishell -ltermcap)