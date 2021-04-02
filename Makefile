# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/24 16:11:07 by ealexa            #+#    #+#              #
#    Updated: 2021/04/02 14:14:48 by ealexa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS				=	./utils
MY_FOLDER			=	./my_folder
NEMY_FOLDER			=	./your_not-folder
SRCS				=	$(UTILS)/list.c\
					$(UTILS)/utils_1.c\
					$(UTILS)/utils_2.c\
					$(MY_FOLDER)/commands.c\
					$(MY_FOLDER)/pwd.c\
					$(MY_FOLDER)/other_cmd_wslesh.c\
					$(MY_FOLDER)/export.c\
					$(MY_FOLDER)/env.c\
					$(MY_FOLDER)/unset.c\
					$(MY_FOLDER)/exit.c\
					$(MY_FOLDER)/echo.c\
					$(MY_FOLDER)/cd.c\
					$(MY_FOLDER)/hist.c\
					$(MY_FOLDER)/gnl_v2.c\
					$(NEMY_FOLDER)/main.c\
					$(NEMY_FOLDER)/parse_shell.c\
					$(NEMY_FOLDER)/parse_shell_utils.c\
					$(NEMY_FOLDER)/create_tokens.c\
					$(NEMY_FOLDER)/create_tokens_utils.c\
					gnl/get_next_line.c\
                       		gnl/get_next_line_utils.c\

OBJ					= $(SRCS:.c=.o)
DIR_INC				= ./include/
CC					= gcc
DEPS				= $(OBJ:%.o=%.d)
RM					= rm -f
CFLAGS				= -I $(DIR_INC) -MMD #-fsanitize=address -Wall -Wextra -Werror
NAME				= minishell

all:			$(NAME)
-include 		$(DEPS)

$(NAME):		$(OBJ)
				${CC} ${CFLAGS} -o ${NAME} ${OBJ} -ltermcap

clean:
				$(RM) $(OBJ) $(DEPS)

fclean:			clean
				$(RM) $(NAME) ${OBJ}

re:				fclean all

bonus:			all

.PHONY:			all clean fclean re
