# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skillian <skillian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 17:39:20 by skillian          #+#    #+#              #
#    Updated: 2022/05/03 14:44:45 by skillian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIBFT = libft/libft.a

SRC = ./a_main.c ./b_philo.c ./c_time.c ./d_utils.c

CC = cc -Wall -Werror -Wextra

OBJ = $(SRC:c=o)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -g -Llibft -lft -fsanitize=thread

$(LIBFT):
	@make --directory=./libft

%.o: %.c
	$(CC) -c $< -o $@ -g -fsanitize=thread

clean:
	@rm -f ./*.o
	@make fclean --directory=./libft

fclean: clean
	rm -f $(NAME) 

re: clean fclean $(NAME)

all: re