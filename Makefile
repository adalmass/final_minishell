NAME = minishell

SRC = main.c \
	  exec/main_exec.c \
	  exec/main_builtins.c \
	  exec/path.c \
	  exec/builtins.c \
	  exec/builtins2.c \
	  exec/builtins3.c \
	  exec/builtins_echo_n.c \
	  exec/utils.c \
	  exec/utils2.c \
	  exec/exec.c \
	  exec/handle_multi.c \
      exec/handle_multi2.c \
	  exec/dollar.c \
	  exec/dollar2.c \
	  exec/redirect.c \
	  exec/redirect2.c \
	  exec/rredirect.c \
	  exec/rredirect3.c \
	  exec/rredirect_input.c \
	  exec/signals.c \
	  exec/export_replace.c \
	  exec/libft/ft_isalphaa.c \
	  exec/libft/ft_split.c \
	  exec/libft/ft_strchr.c \
	  exec/libft/ft_strdup.c \
	  exec/libft/ft_strjoin.c \
	  exec/libft/ft_strlenn.c \
	  exec/libft/ft_strncmp.c \
	  exec/libft/ft_strtrim.c \
	  exec/libft/ft_calloc.c \
	  exec/libft/ft_atoi.c \
	  exec/libft/ft_substr.c \
	  parsing/parsing.c \
	  parsing/check_cmd.c \
	  parsing/tools.c \
	  parsing/utils.c \
	  parsing/redir_n_pipe.c \
	  parsing/handle_quotes.c \
	  parsing/handle_quotes2.c \
	  parsing/handle_pipes.c \
	  parsing/mini_libft/ft_strdup.c \
	  parsing/mini_libft/ft_strjoin.c \
	  parsing/mini_libft/ft_strcpy.c \
	  parsing/mini_libft/ft_isalpha.c \
	  parsing/mini_libft/ft_isalnum.c \
	  parsing/mini_libft/ft_isdigit.c \
	  parsing/mini_libft/ft_strjoin_free.c \
	  parsing/mini_libft/ft_strncmp.c \
	  parsing/mini_libft/ft_strtrim.c \
	  parsing/mini_libft/ft_strlen.c \
	  parsing/mini_libft/ft_memcpy.c \
	  parsing/mini_libft/ft_strnstr.c \
	  parsing/mini_libft/ft_split.c \
	  parsing/mini_libft/ft_putstr_fd.c \
	  parsing/mini_libft/ft_putchar.c \
	  parsing/mini_libft/ft_strchr.c \
	  parsing/mini_libft/ft_substr.c \

OBJ = $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror #-fsanitize=address

.c.o = $(CC) -c -o $(OBJ)

$(NAME): $(OBJ)
	@${CC} $(OBJ) -o $(NAME) -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
	@echo "Archivage terminé [minishell]"

all: $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "Suppression des .o" 

fclean: clean
	@rm -f $(OBJ) $(NAME)
	@echo "Suppression du .a effectuée"

re: fclean all

.PHONY : all clean fclean re
