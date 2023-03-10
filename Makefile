# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 16:29:13 by adbenoit          #+#    #+#              #
#    Updated: 2023/01/25 17:16:08 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION
CC		= gcc
CFLAGS 	= -Wall -Wextra -Werror
IFLAGS 	= -I./incs

UNAME	:= $(shell uname)
ifeq ($(UNAME), Darwin)
	CFLAGS += -DOS
endif

# DIRECTORIES
BUILD 			:= .build
SRC_DIR 		:= srcs
OBJ_DIR 		:= $(BUILD)/obj
SUB_DIR			:= parsing
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

SHARED_FILE		:= shared_memory

# FILES
NAME			:= lemipc
SRC				:=	main.c \
					map.c \
					env.c \
					player.c \
					target.c \
					game.c \
					move.c \
					utils.c \
					parsing.c

OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)


# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_GREY	 		= \033[1;38m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m
B_BLUE 			= \033[1;34m
B_YELLOW 		= \033[1;33m
B_WHITE 		= \033[1;37m

# STATUS
DELETE			= "\ \ "$(B_MAGENTA)"DELETE"$(NONE)"\ \ "
RESET			= "\ \ \ "$(B_YELLOW)"RESET"$(NONE)"\ \ "
OK				= "\ \ \ \ "$(B_GREEN)"OK"$(NONE)"\ \ \ \ "
KO				= "\ \ \ \ "$(B_RED)"KO"$(NONE)"\ \ \ \ "
LINK_OK			= "\ \ \ "$(B_YELLOW)"LINK"$(NONE)"\ \ \ "
LINK_KO			= ""$(B_RED)"LINK ERROR"$(NONE)""
COMP			= "\ "$(B_CYAN)"COMPILING"$(NONE)""

# MAKEFILE
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)
	@echo "$(CL_LINE)[$(OK)] $@"

all: $(NAME)

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@printf "$(CL_LINE)[$(COMP)] $< ...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@rm -Rf $(BUILD)
	@echo "[$(DELETE)] $(BUILD)"

fclean: clean
	@rm -Rf $(LINK_NAME) $(NAME) $(TEST_EXEC) $(SHARED_FILE)
	@echo "[$(DELETE)] $(NAME)"

re: fclean all

run: $(NAME)

debug: CFLAGS += -DDEBUG -DLOG -g2 -fsanitize=address
debug: re

log: CFLAGS += -DLOG
log: re

debug_make:
	@echo $(SRC)

.PHONY: all clean fclean re debug run
