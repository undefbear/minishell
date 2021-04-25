# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/24 16:11:07 by ealexa            #+#    #+#              #
#    Updated: 2021/04/18 18:09:10 by ealexa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS				=	./utils
MY_FOLDER			=	./my_folder
NEMY_FOLDER			=	./your_not-folder
SRCS				=	$(UTILS)/list.c\
					$(UTILS)/list_2.c\
					$(UTILS)/utils_1.c\
					$(UTILS)/utils_2.c\
					$(UTILS)/utils_3.c\
					$(UTILS)/utils_4.c\
					$(MY_FOLDER)/commands.c\
					$(MY_FOLDER)/pwd.c\
					$(MY_FOLDER)/other_cmd_wslesh.c\
					$(MY_FOLDER)/export.c\
					$(MY_FOLDER)/export_2.c\
					$(MY_FOLDER)/my_utils.c\
					$(MY_FOLDER)/press_keys.c\
					$(MY_FOLDER)/change_value.c\
					$(MY_FOLDER)/env.c\
					$(MY_FOLDER)/other_cmds.c\
					$(MY_FOLDER)/other_cmds_2.c\
					$(MY_FOLDER)/unset.c\
					$(MY_FOLDER)/delete_sym.c\
					$(MY_FOLDER)/errors_code.c\
					$(MY_FOLDER)/exit.c\
					$(MY_FOLDER)/echo.c\
					$(MY_FOLDER)/cd.c\
					$(MY_FOLDER)/hist.c\
					$(MY_FOLDER)/gnl_v2.c\
					$(NEMY_FOLDER)/main.c\
					$(NEMY_FOLDER)/make_redir.c\
					$(NEMY_FOLDER)/make_redir_utils.c\
					$(NEMY_FOLDER)/parse_shell.c\
					$(NEMY_FOLDER)/parse_shell_utils.c\
					$(NEMY_FOLDER)/create_tokens.c\
					$(NEMY_FOLDER)/create_tokens_utils.c\
					$(NEMY_FOLDER)/hi_pipe.c\

OBJ					= $(SRCS:.c=.o)
DIR_INC				= ./include/
CC					= gcc
DEPS				= @$(OBJ:%.o=%.d)
RM					= rm -f
CFLAGS				= -I $(DIR_INC) -MMD  -Wall -Wextra -Werror# -fsanitize=address
NAME				= minishell

.c.o:
					@printf "\033[1;37m\033[2m - i'm preparing minishell... %-33.33s\r" $@
					@${CC} ${CFLAGS} -c $< -o $@

all:			$(NAME)

-include 		$(DEPS)

$(NAME):		$(OBJ)
				@${CC} ${CFLAGS} -o ${NAME} ${OBJ} -ltermcap
				@echo "\033[1;34m\033[2m \n - ok, minishell is ready, run it and try to write smth"

clean:
				@echo "\033[1;34m\033[2m - well, i cleaned all objects files \033[0m"
				@ rm -rf ./utils/list.d
				@$(RM) $(OBJ) $(DEPS)

fclean:			clean
				@echo "\033[1;34m\033[2m - also i removed executable \033[0m"
				@$(RM) $(NAME) ${OBJ}


re:				fclean all

bonus:			all

.PHONY:			all clean fclean re
