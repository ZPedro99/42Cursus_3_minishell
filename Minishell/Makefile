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

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME) minishell

re: fclean all