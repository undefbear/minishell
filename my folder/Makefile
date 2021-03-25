# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/24 16:11:07 by ealexa            #+#    #+#              #
#    Updated: 2021/03/25 16:56:58 by ealexa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS				=	../utils

SRCS				=	$(UTILS)/list.c $(UTILS)/utils_1.c main.c $(UTILS)/utils_2.c pwd.c other_cmd_wslesh.c \
						export.c

OBJ					= $(SRCS:.c=.o)
DIR_INC	= ../include/
CC					= gcc
DEPS				= $(OBJ:%.o=%.d)
RM					= rm -f
CFLAGS				= -I $(DIR_INC) -MMD -fsanitize=address -Wall -Wextra -Werror
NAME				= commans
   
all:			$(NAME)
-include 		$(DEPS)

$(NAME):		$(OBJ)
				${CC} ${CFLAGS} -o ${NAME} ${OBJ}

clean:
				$(RM) $(OBJ) $(DEPS)

fclean:			clean
				$(RM) $(NAME) ${OBJ}

re:				fclean all

bonus:			all

.PHONY:			all clean fclean re