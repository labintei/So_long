# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labintei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 14:05:41 by labintei          #+#    #+#              #
#    Updated: 2021/05/19 09:37:06 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	bmp.c checkbeforeopen.c checkbis.c dra.c drawray4.c drawray5.c\
				last.c openmap7.c parse.c texture.c utils.c variables.c stock.c
DIR_MLX		=	./minilibx/

OBJS		= $(SRCS:.c=.o)

CC				= gcc
CFLAGS			= -g -fsanitize=address -Wall -Wextra -Werror -I includes.
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
