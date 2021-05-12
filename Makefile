# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labintei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 14:05:41 by labintei          #+#    #+#              #
#    Updated: 2021/05/12 19:01:05 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	bmp.c checkbeforeopen.c checkbis.c dra.c drawray4.c drawray5.c\
				last.c openmap7.c parse.c texture.c utils.c variables.c
DIR_MLX		=	./minilibx/

OBJS		= $(SRCS:.c=.o)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I includes.
LIBS			= -L ./minilibx/ -lmlx -lXext -lX11 -lm
RM				= rm -f
NAME			= cub3D

all:		$(NAME)

$(NAME): 
				gcc ${CFLAGS} ${SRCS} ${LIBS} -o $(NAME)

clean:
				$(RM) $(NAME)

fclean:			
				$(RM) $(NAME)

re: clean all

.PHONY:		all clean fclean re
