UNAME_S		:=	$(shell uname -s)
IS_MACOS	:=	$(filter Darwin, $(UNAME_S))
IS_LINUX	:=	$(filter Linux,$(UNAME_S))

SRCDIR 	=	./src
SRCS	=	$(SRCDIR)/fdf.c			\
			$(SRCDIR)/map-parser.c	\
			$(SRCDIR)/map-drawing.c	\
			$(SRCDIR)/key-hook.c	\
			$(SRCDIR)/colors.c		\
			$(SRCDIR)/projections.c

OBJS	=	$(SRCS:.c=.o)

LIBFT_DIR	= libs/libft
LIBFT_BIN	= $(LIBFT_DIR)/libft.a

ifeq ($(IS_MACOS),Darwin)
	PLATFORM	= macos
	NAME		= fdf
	MLX_DIR		= ./libs/minilibx-macos
	MLX_BIN		= $(MLX_DIR)/libmlx.a

	CFLAGS		= -I$(MLX_DIR)
	FRAMEWORKS	= -framework OpenGL -framework AppKit -lm
	LDFLAGS		= $(MLX_DIR) $(FRAMEWORKS)

	DEBUG_CFLAGS	= -pedantic-errors -fsanitize=address,undefined
	DEBUG_LDFLAGS	= -fsanitize=address,undefined
endif

ifeq ($(IS_LINUX),Linux)
	PLATFORM	= linux
	NAME		= fdf
	MLX_DIR		= ./libs/minilibx-linux
	MLX_BIN		= $(MLX_DIR)/libmlx.a

	CFLAGS		= -I$(MLX_DIR)
	FRAMEWORKS	= -lX11 -lXext -lm 
	LDFLAGS		= $(MLX_DIR) $(FRAMEWORKS)

	DEBUG_CFLAGS	= -pedantic-errors -fsanitize=address,undefined
	DEBUG_LDFLAGS	= -fsanitize=address,undefined
endif

ifndef PLATFORM
	$(error Unsupported platform)
endif


$(NAME): $(OBJS) $(LIBFT_BIN) $(MLX_BIN)
	cp -f $(MLX_DIR)/mlx.h $(SRCDIR)/mlx.h
	$(CC) $(OBJS) $(MLX_BIN) $(LIBFT_BIN) -o $(NAME) -I $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_BIN):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_BIN):
	$(MAKE) -C $(MLX_DIR) CFLAGS="-I$(MLX_DIR)" LDFLAGS="-L$(MLX_DIR)" VERBOSE=1

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_CFLAGS)" LDFLAGS="$(LDFLAGS) $(DEBUG_LDFLAGS)" all

re: fclean all $(LIBFT_DIR) $(MLX_DIR)

