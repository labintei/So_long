# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labintei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 14:05:41 by labintei          #+#    #+#              #
#    Updated: 2021/06/19 13:36:58 by labintei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS		=	test.c
SRCS		=	parse.c get_next_line.c get_next_line_utils.c load_texture.c
DIR_MLX		=	./minilibx/

OBJS		= $(SRCS:.c=.o)

CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror -I includes.
LIBS			= -L ./minilibx/ -lmlx -lXext -lX11 -lm
RM				= rm -f
NAME			= cub3D

all:		${NAME}
.c.o:
				${CC} ${CFLAGS} -Imlx -Ibass -c $< -o ${<:c=o}

$(NAME):	$(OBJS)
				make -C $(DIR_MLX)
				${CC} $(CFLAGS) -o $(NAME) $(SRCS) $(LIBS)
				${MACH_EXTRA}

clean:
				make -C $(DIR_MLX) clean
				$(RM) $(OBJS)

fclean:			
				make -C $(DIR_MLX) clean
				$(RM) $(NAME)

re: clean all

.PHONY:		all clean fclean re
