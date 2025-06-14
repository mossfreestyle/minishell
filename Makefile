NAME = minishell


SRCDIR = src
PARSEDIR = src/parsing
LIBFTDIR = libft
INCDIR = includes


SRCS = $(SRCDIR)/main.c $(PARSEDIR)/lexer.c $(PARSEDIR)/quotes.c

OBJS = $(SRCS:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCDIR) -I$(LIBFTDIR)
LIBS = -lreadline -L$(LIBFTDIR) -lft


LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME)


$(LIBFT):
	@make -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
