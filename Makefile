# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Champi <Champi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 18:05:54 by dzheng            #+#    #+#              #
#    Updated: 2017/02/16 01:13:53 by Champi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = cc
FLAGS = -Wall -Wextra -Werror
SRCS = 	ft_ls.c ft_ls_front.c ft_ls_rec.c ft_ls_front_colors.c				\
		ft_ls_back.c ft_ls_back_sort.c ft_ls_back_args.c					\
		ft_ls_back_args_sort.c
PATH_SRC = ./srcs/
SRC = $(addprefix ${PATH_SRC}, $(SRCS))
LIB_PATH = ./libft/
LIB = $(LIB_PATH)/libft.a
CFLAGS = -Wall -Werror -Wextra

#COLORS
C_GOOD			=	"\033[32m"

#MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$

all : $(NAME)

$(NAME): 
		@make -C ./libft/
		@$(CC) $(FLAGS) $(SRC) -I. -I./libft/ $(LIB) -o $(NAME)
		@echo "Compiling" [ $(NAME) ] $(SUCCESS)

cc:		
		@$(CC) $(FLAGS) $(SRC) -I. -I./libft/ $(LIB) -o $(NAME)
		./ft_ls -Rl

clean:
		make -C ./libft/ clean

fclean: clean
		/bin/rm -f $(NAME)
		make -C ./libft/ fclean

re: fclean all

.PHONY: all clean fclean re