NAME			= test

OBJDIR			= obj/
INCDIR			= ../../../include/
LIBFT_DIR		= ../../../libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRCS			= src/built_in/main.c \
                  src/built_in/env.c \
                  src/built_in/pwd.c

OBJS			= $(SRCS:src/%.c=$(OBJDIR)%.o)

CC				= cc
INCLUDES		= -I $(INCDIR) -I $(LIBFT_DIR)/include
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Règle générique qui gère tous les sous-dossiers
$(OBJDIR)%.o: src/%.c $(INCDIR)/minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
