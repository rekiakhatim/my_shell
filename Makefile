NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
FLAGS = -lreadline
INCLUDES = -I .
SRCS = $(wildcard srcs/*.c) #srcs/minishell.c srcs/parsing.c srcs/heredoc.c srcs/libft.c srcs/list.c srcs/list2.c\
	srcs/ft_error.c srcs/tokenizing.c srcs/expand.c srcs/expand2.c srcs/expand3.c srcs/ft_free.c srcs/help.c\
	srcs/utils.c srcs/utils2.c #built_in.c export_fcts.c export_fctss.c ft_cd.c ft_echo.c\
	ft_env.c free.c ft_exit.c ft_pwd.c ft_unset.c print_export.c pipe.c 
OBJC = $(SRCS:.c=.o)
LIBFT = lib_ft/libft.a

all: $(NAME)


$(NAME): $(LIBFT) $(OBJC)
	@$(CC) $(INCLUDES) $(CFLAGS) $(OBJC) $(LIBFT) $(FLAGS) -o minishell
	@echo "executable file is ready"

$(LIBFT):
	make -C lib_ft

.c.o:
	@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@
clean:
	make clean -C lib_ft
	@rm -f $(OBJC)
	@echo "objects removed"

fclean:
	make fclean -C lib_ft
	@rm  -f $(OBJC) $(NAME)
	@echo "objects and executable removed"

re: fclean all