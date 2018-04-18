NAME = rt

# **************************************************************************** #

# COMPILATION 
CC = clang
CCFLAGS = -Wall -Wextra -Werror -O2 -flto
FRMW = -framework AppKit -framework OpenGL -lpthread

# DIRECTORIES
D_SRC = srcs
D_INC = inc
D_OBJ = obj
D_LIBFT = libft
D_MLX = minilibx

#LIBRARIES
LDL = $(addprefix -L, $(D_LIBFT))
LDM = $(addprefix -L, $(D_MLX))

# SOURCES
F_SRC =\
		main.c \
		build_map.c \
		check_params.c \
		check_config_1.c \
		check_config_2.c \
		parse_plane.c \
		parse_sphere.c \
		parse_cone.c \
		parse_light.c \
		parse_cylinder.c \
		parse_hyperbol.c \
		init_vec.c \
		display.c \
		threads_op.c \
		key.c \
		key2.c \
		raytracer.c \
		init_raytracer.c \
		intersect.c \
		calcs.c \
		calcs2.c \
		lights.c \
		norm.c \
		norm2.c \
		image.c \
		shadows.c \
		rotation.c \
		rothit.c \
		mouse.c \
		reflexion.c \
		reflexion2.c \
		export_config.c \
		export_config_2.c \
		export_config_3.c \
		check_config_3.c \
		levels.c \
		rotforms.c \
		caps.c \
		export_image.c \
		add_objects.c \
		export_config.c \
		export_config_2.c \
		interface.c \
		interface2.c \
		filter.c \
		bdperlin.c \
		intersect2.c \

# ***************************************************************************** #

# SPECIAL CHARS
LOG_CLEAR               = \033[2K
LOG_UP                  = \033[A
LOG_NOCOLOR             = \033[0m
LOG_BLACK               = \033[1;30m
LOG_RED                 = \033[1;31m
LOG_GREEN               = \033[1;32m
LOG_YELLOW              = \033[1;33m
LOG_BLUE                = \033[1;34m
LOG_VIOLET              = \033[1;35m
LOG_CYAN                = \033[1;36m
LOG_WHITE               = \033[1;37m

# ****************************************************************************** #

.PHONY: make all fclean re

F_OBJ = $(addsuffix .o, $(basename $(F_SRC)))

DF_SRC = $(addprefix $(D_SRC)/, $(F_SRC))
DF_OBJ = $(addprefix $(D_OBJ)/, $(F_OBJ))

RM = /bin/rm -rf

all: $(NAME)

$(D_OBJ)/%.o: $(D_SRC)/%.c $(D_INC)
	@mkdir -p $(D_OBJ) 2> /dev/null || true
	@echo "$(LOG_CYAN)$(NAME)... $(LOG_NOCOLOR)$<"
	@$(CC) $(CCFLAGS) -I $(D_INC) -o $@ -c $<
$(NAME): $(DF_OBJ)
	@make -C $(D_LIBFT)
	@echo "$(LOG_YELLOW)MLX... assembling...$(LOG_NOCOLOR)"
	@make -C $(D_MLX)
	@echo "$(LOG_GREEN)MLX... compiled ✓$(LOG_NOCOLOR)"
	@echo "$(LOG_CYAN)$(NAME)... assembling...$(LOG_NOCOLOR)"
	@$(CC) $(CCFLAGS) $(LDL) -lft $(LDM) -lmlx $^ -o $@ $(FRMW)
	@echo "$(LOG_GREEN)$(NAME)... compiled ✓$(LOG_NOCOLOR)"
clean:
	@echo "$(LOG_RED)Deleting $(NAME)'s objs ✖$(LOG_NOCOLOR)"
	@$(RM) $(D_OBJ)
fclean: clean
	@echo "$(LOG_RED)Deleting $(NAME) ✖$(LOG_NOCOLOR)"
	@$(RM) $(NAME)
	@make fclean -C $(D_LIBFT)
	@make clean -C $(D_MLX)
re: fclean all
