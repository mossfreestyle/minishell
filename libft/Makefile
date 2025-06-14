NAME= 		libft.a
CC= 		gcc -Wall -Wextra -Werror
SRCDIR= 	src/check src/convert src/ft_printf src/get_next_line src/list src/mem src/put src/str
INCDIR= 	include/
SRCS= 		$(foreach d, $(SRCDIR), $(wildcard $(d)/*.c))
OBJS= 		$(SRCS:.c=.o)
RM= 		rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(INCDIR)libft.h
				@ar rcs $@ $^

%.o: %.c $(INCDIR)libft.h
				@$(CC) -I$(INCDIR) -c $< -o $@

clean:
				@$(RM) $(OBJS)

fclean:		clean
				@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re