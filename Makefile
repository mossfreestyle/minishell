NAME			= minishell

OBJDIR			= obj/
INCDIR			= include/

SRCS			= src/main.c \
				  src/parser/tokenize.c \
				  src/parser/utils_parser.c \
				  src/utils/free.c

OBJS			= $(SRCS:src/%.c=$(OBJDIR)%.o)

LIBFT_DIR		= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a

CC				= cc
INCLUDES		= -I $(INCDIR) -I $(LIBFT_DIR)/include
CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			= -lreadline
RM				= rm -f

all:			$(NAME)

$(NAME): 		$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(OBJDIR)%.o:	src/%.c $(INCDIR)/minishell.h
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
				@$(MAKE) -C $(LIBFT_DIR)

clean:
				rm -rf $(OBJDIR)
				@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
				$(RM) $(NAME)
				rm -rf $(OBJDIR)
				@$(MAKE) -C $(LIBFT_DIR) fclean

re: 			fclean all

.PHONY: 		all clean fclean re
