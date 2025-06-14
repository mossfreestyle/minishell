NAME        = test

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCDIR      = ../../../include
LIBFT_DIR   = ../../../libft
LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(INCDIR) -I$(LIBFT_DIR)/include

SRCDIR      = src
OBJDIR      = obj

# Trouve tous les .c dans src/ et sous-dossiers
SRCS        = $(wildcard $(SRCDIR)/**/*.c)
OBJS        = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
