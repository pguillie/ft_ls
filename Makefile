# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 12:33:46 by pguillie          #+#    #+#              #
#    Updated: 2017/04/07 18:11:55 by pguillie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ls
CC			= gcc
FLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I./includes
LIBPATH		= ../libft/
LIB			= $(LIBPATH)libft.a

SOURCES	= \
		  ft_ls_add.c\
		  ft_ls_arg_file.c\
		  ft_ls_arg_opt.c\
		  ft_ls_clean.c\
		  ft_ls_disp_fields.c\
		  ft_ls_disp_filetype.c\
		  ft_ls_disp_mode.c\
		  ft_ls_display.c\
		  ft_ls_error.c\
		  ft_ls_layout.c\
		  ft_ls_format.c\
		  ft_ls_list_new.c\
		  ft_ls_open_file.c\
		  ft_ls_srch_opt.c\
		  ft_ls_showdirname.c\
		  ls_sort_functions.c\
		  main.c\

OBJECTS	= $(SOURCES:.c=.o)

RED		= \033[31;01m
GREEN	= \033[32;01m
BLUE	= \033[34;01m
WHITE	= \033[37;01m
EOC		= \033[0m

all : $(NAME)

$(NAME) : $(OBJECTS)
	@ make -C $(LIBPATH)
	@ $(CC) $(FLAGS) -o $@ $^ $(LIB) -lm $(LINK)
	@ echo "\n$(GREEN)$@ successfully created !$(EOC)\n"

%.o : %.c
	@ $(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<
	@ echo "$(BLUE)• $(WHITE)$(notdir $(basename $@))$(GREEN) √$(EOC)"

clean :
	@ make -C $(LIBPATH) clean
	@ rm -rf $(OBJECTS)
	@ echo "$(RED)$(NAME) object files deleted$(EOC)\n"

fclean : clean
	@ rm -rf $(LIBPATH)libft.a
	@ echo "$(RED)libft.a deleted$(EOC)\n"
	@ rm -rf $(NAME)
	@ echo "$(RED)$(NAME) deleted$(EOC)\n"

re : fclean all
