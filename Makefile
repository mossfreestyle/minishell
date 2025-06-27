# ================================= COLORS ================================== #
RESET		= \033[0m
BOLD		= \033[1m
DIM			= \033[2m
UNDERLINE	= \033[4m

# Regular Colors
BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m

# Background Colors
BG_BLACK	= \033[40m
BG_RED		= \033[41m
BG_GREEN	= \033[42m
BG_YELLOW	= \033[43m
BG_BLUE		= \033[44m
BG_MAGENTA	= \033[45m
BG_CYAN		= \033[46m
BG_WHITE	= \033[47m

# High Intensity Colors
HI_BLACK	= \033[90m
HI_RED		= \033[91m
HI_GREEN	= \033[92m
HI_YELLOW	= \033[93m
HI_BLUE		= \033[94m
HI_MAGENTA	= \033[95m
HI_CYAN		= \033[96m
HI_WHITE	= \033[97m

# ================================ VARIABLES ================================= #
NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= -I./include -I./libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= -L$(LIBFT_DIR) -lft -lreadline

# ================================= SOURCES ================================== #
SRC_DIR		= src
EXEC_DIR	= $(SRC_DIR)/exec/src
PARSER_DIR	= $(SRC_DIR)/parser
UTILS_DIR	= $(SRC_DIR)/utils
BUILTIN_DIR	= $(EXEC_DIR)/built_in
CMD_DIR = $(EXEC_DIR)/cmd

MAIN_FILES	= main.c

PARSER_FILES = tokenize.c \
               quotes.c \
               utils_parser.c \
			   lexer.c \
			   syntax.c \
			   extract.c \
			   parser.c

UTILS_FILES	= free.c \
              error.c \
			  env.c \
			  utils_str.c \
			  signals.c \
			  init.c \
			  utils2.c \
			  utils.c

BUILTIN_FILES = cd.c \
                echo.c \
                env.c \
                exit.c \
				export_scd.c \
				export.c \
				pwd.c \
				unset.c

CMD_FILES = exec_built_in.c \
			exec_commands.c \
			exec_here_doc.c \
			exec_readline.c \
			find_paths.c \
			handle_redirections.c \
			init.c \
			utils.c \
			close_and_free.c \
			here_doc_utils.c

SRCS		= $(addprefix $(SRC_DIR)/, $(MAIN_FILES)) \
              $(addprefix $(PARSER_DIR)/, $(PARSER_FILES)) \
              $(addprefix $(UTILS_DIR)/, $(UTILS_FILES)) \
              $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES)) \
			  $(addprefix $(CMD_DIR)/, $(CMD_FILES))


OBJ_DIR		= obj
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ================================== RULES =================================== #

all: header $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(HI_CYAN)$(BOLD)🔗 Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(HI_GREEN)$(BOLD)✅ $(NAME) compiled successfully!$(RESET)\n"
	@printf "$(HI_MAGENTA)$(BOLD)🚀 Ready to execute: ./$(NAME)$(RESET)\n\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(HI_BLUE)⚙️  Compiling $(YELLOW)$(notdir $<)$(RESET)$(HI_BLUE)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@printf "$(HI_YELLOW)$(BOLD)📚 Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(HI_GREEN)✅ Libft compiled!$(RESET)\n"

clean:
	@printf "$(HI_RED)$(BOLD)🧹 Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@printf "$(HI_GREEN)✅ Clean completed!$(RESET)\n"

fclean: clean
	@printf "$(HI_RED)$(BOLD)🗑️  Removing $(NAME)...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@printf "$(HI_GREEN)✅ Full clean completed!$(RESET)\n"

re: fclean all

header:
	@printf "$(HI_CYAN)$(BOLD)"
	@printf "╔══════════════════════════════════════════════════════════════════════╗\n"
	@printf "║                                                                      ║\n"
	@printf "║$(HI_MAGENTA)                           🐚 MINISHELL 🐚                           $(HI_CYAN)║\n"
	@printf "║                                                                      ║\n"
	@printf "║$(HI_WHITE)                    A minimal Unix shell implementation               $(HI_CYAN)║\n"
	@printf "║                                                                      ║\n"
	@printf "║$(HI_YELLOW)                         By: rwassim & mfernand                      $(HI_CYAN)║\n"
	@printf "║                                                                      ║\n"
	@printf "╚══════════════════════════════════════════════════════════════════════╝\n"
	@printf "$(RESET)\n"

.PHONY: all clean fclean re header

# ================================== INFO ==================================== #
info:
	@printf "$(HI_CYAN)$(BOLD)📋 Project Information:$(RESET)\n"
	@printf "$(HI_WHITE)• Name: $(HI_YELLOW)$(NAME)$(RESET)\n"
	@printf "$(HI_WHITE)• Compiler: $(HI_YELLOW)$(CC)$(RESET)\n"
	@printf "$(HI_WHITE)• Flags: $(HI_YELLOW)$(CFLAGS)$(RESET)\n"
	@printf "$(HI_WHITE)• Sources: $(HI_YELLOW)$(words $(SRCS)) files$(RESET)\n"
	@printf "$(HI_WHITE)• Objects: $(HI_YELLOW)$(OBJ_DIR)/$(RESET)\n"
	@printf "$(HI_WHITE)• Libraries: $(HI_YELLOW)libft, readline$(RESET)\n\n"

help:
	@printf "$(HI_CYAN)$(BOLD)🆘 Available targets:$(RESET)\n"
	@printf "$(HI_GREEN)• all$(RESET)     - Compile the project\n"
	@printf "$(HI_GREEN)• clean$(RESET)   - Remove object files\n"
	@printf "$(HI_GREEN)• fclean$(RESET)  - Remove object files and executable\n"
	@printf "$(HI_GREEN)• re$(RESET)      - Recompile the project\n"
	@printf "$(HI_GREEN)• info$(RESET)    - Show project information\n"
	@printf "$(HI_GREEN)• help$(RESET)    - Show this help message\n\n"
