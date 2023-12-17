# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 15:10:07 by rpliego           #+#    #+#              #
#    Updated: 2023/12/07 21:11:29 by rpliego          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -pthread
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRC =	main.c \
		init.c \
		utils.c \
		threads.c

OBJ = $(SRC:.c=.o)
INCLUDE = philo.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE) Makefile
	$(CC) $(CFLAGS) -fsanitize=thread -g -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re