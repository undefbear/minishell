cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell
        utils/list.c
        utils/list_2.c
        utils/utils_1.c
        utils/utils_2.c
        utils/utils_3.c
        utils/utils_4.c
        my_folder/commands.c
        my_folder/pwd.c
        my_folder/other_cmd_wslesh.c
        my_folder/export.c
        my_folder/export_2.c
        my_folder/my_utils.c
        my_folder/press_keys.c
        my_folder/change_value.c
        my_folder/env.c
        my_folder/other_cmds.c
        my_folder/other_cmds_2.c
        my_folder/unset.c
        my_folder/delete_sym.c
        my_folder/errors_code.c
        my_folder/exit.c
        my_folder/echo.c
        my_folder/cd.c
        my_folder/hist.c
        my_folder/gnl_v2.c
        your_not-folder/main.c
        your_not-folder/make_redir.c
        your_not-folder/parse_shell.c
        your_not-folder/parse_shell_utils.c
        your_not-folder/create_tokens.c
        your_not-folder/create_tokens_utils.c
        your_not-folder/hi_pipe.c
        your_not-folder/make_redir_utils.c)

target_link_libraries(minishell -ltermcap)