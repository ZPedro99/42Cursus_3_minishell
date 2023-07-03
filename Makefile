# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:54:12 by emsoares          #+#    #+#              #
#    Updated: 2023/06/28 15:23:37 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RFLAG = -lreadline
RM = rm -rf

LIBFT = ./libft/libft.a

SRCS = main.c\
		env.c\
		env2.c\
		export.c\
		export2.c\
		export3.c\
		free.c\
		execute.c\
		pwd.c\
		echo.c\
		echo_utils.c\
		echo_utils2.c\
		cd.c\
		cd2.c\
		utils.c\
		utils2.c\
		unset.c\
		signals.c\
		exit.c\
		multi_commands.c\
		single_command.c\
		redirects.c\

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RFLAG) -o $(NAME)

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME) push_swap

re: fclean all