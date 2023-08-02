# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:54:12 by emsoares          #+#    #+#              #
#    Updated: 2023/07/26 14:28:28 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m


NAME = minishell
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RFLAG = -lreadline
RM = rm -rf
LIBFT = ./libft/libft.a

SRCS = main.c \
		builtins.c \
		builtins2.c \
		cd.c \
		cd2.c \
		echo_utils.c \
		echo.c \
		echo2.c \
		env.c \
		env2.c \
		execute.c \
		exit_utils.c \
		exit_utils2.c \
		exit.c \
		expander.c \
		expander2.c \
		expander3.c \
		expander4.c \
		export.c \
		export2.c \
		export3.c \
		export4.c \
		export5.c \
		free.c \
		free2.c \
		free3.c \
		main2.c \
		multi_commands.c \
		pwd.c \
		redirects.c \
		redirects2.c \
		redirects3.c \
		signals.c \
		single_command.c \
		single_command2.c \
		single_command3.c \
		unset.c \
		unset2.c \
		utils.c \
		utils2.c \
		utils3.c \
		utils4.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RFLAG) -o $(NAME)
	echo "$(GREEN)Minishell executable is ready!$(RESET)"

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJS)
	echo "$(RED)Object files have been deleted!$(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME) minishell
	echo "$(RED)Object and Executable files have been deleted!$(RESET)"

re: fclean all

.SILENT: