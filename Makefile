# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzheng <dzheng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 18:05:54 by dzheng            #+#    #+#              #
#    Updated: 2017/02/15 18:06:24 by dzheng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBNAME = libft.a
LIBPATH = ./libft/

OBJDIR = objs

SRC = 	ft_ls.c ft_ls_front.c ft_ls_rec.c ft_ls_front_colors.c \
		ft_ls_back.c ft_ls_back_sort.c ft_ls_back_args.c
SRCDIR = ./srcs/
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra
CC = gcc
RM = rm -rf

all : $(NAME)

$(NAME) :
	@make -C libft/ re
	@echo "\t\033[33;32m'MAKE' ->\t\033[1;34m$(NAME)\033[0m :\tCompilation in progress..."
	@gcc -o $(NAME) $(CFLAGS) -Ilibft/ -I. $(addprefix $(SRCDIR), $(SRC)) $(addprefix $(LIBPATH), $(LIBNAME))
	@echo "\t\033[33;32m'MAKE' ->\t\033[1;34m$(NAME)\033[0m :\tLibrary compilation completed sucessfully !"

cc :
	@echo "\t\033[33m'COMPILE NO FLAGS' ->\t\033[1;34m$(NAME)\033[0m :\tExecutable compilation in progress..."
	@gcc -o $(NAME) -Ilibft/libft.h -Ift_ls.h $(addprefix $(SRCDIR), $(SRC)) $(addprefix $(LIBPATH), $(LIBNAME))
	@echo "\t\033[33m'COMPILE NO FLAGS' ->\t\033[1;34m$(NAME)\033[0m :\tCompilation completed sucessfully !"
clean :
	@echo "\t\033[1;31m'CLEAN' ->\tDestruction\033[0m:\tfiles .o for the program \033[1;34m$(NAME)\033[0m"
	@$(RM) $(OBJ)
	@make -C libft/ clean

fclean : clean
	@$(RM) $(NAME)
	@echo "\t\033[1;31m'FCLEAN' ->\tDestruction\033[0m\tof program \033[1;34m$(NAME)\033[0m"
	@make -C libft/ fclean

re : fclean all

.PHONY: all clean fclean re