NAME = minishell
CC = gcc
INCLUDES = -Iinclude -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include
#CFLAGS = -Wall -Wextra -Werror -g3 -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline
#LDFLAGS = -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -g -g3 -fsanitize=address


SRCS =	src_joe/minishell.c \
		src_joe/parsing.c \
		src_shi/ft_parsing.c \
		src_joe/ft_heredoc.c \
		src_shi/ft_lexer_utils.c \
		src_joe/built_in1.c \
		src_joe/built_in2.c \
		src_joe/built_in3.c \
		src_joe/ft_chevron.c \
		src_joe/ft_error.c \
		src_joe/ft_execution.c \
		src_shi/ft_lexer.c \
		src_joe/pipe_utils.c \
		src_joe/pipe.c \
		src_joe/signals.c \
		src_joe/utils1.c \
		src_joe/utils2.c \
		src_shi/ft_operation_for_lexing.c \
		src_shi/ft_split_minishell_utils.c \
		src_joe/ft_cd.c \
		src_joe/ft_chevron_utils.c \
		src_joe/ft_heredoc_utils.c \
		src_joe/utils3.c \
		src_shi/ft_lexer_2.c \
        src_shi/ft_lexer_3.c \

LIB = libft/libft.a
OBJS = $(SRCS:.c=.o)
 
all : $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(LIB) -o $@ $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(HEADER) -g -c $< -o $@

$(LIB):
	make -C ./libft

clean:
	make clean -C ./libft
	rm -rf $(OBJS)

fclean:
	make fclean -C ./libft
	rm -rf $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
