# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 15:10:07 by rpliego           #+#    #+#              #
#    Updated: 2024/04/25 18:59:17 by rpliego          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread
RM = rm -rf

SRC =	main.c \
		init.c \
		check_args.c \
		threads.c \
		utils.c \
		actions.c

OBJ = $(SRC:.c=.o)
INCLUDE = philo.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE) Makefile
	$(CC) -pthread $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re