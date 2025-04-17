UNAME_S		:=	$(shell uname -s)
IS_MACOS	:=	$(filter Darwin, $(UNAME_S))
IS_LINUX	:=	$(filter Linux,$(UNAME_S))

SRCS	=	fdf.c			\
			map-parser.c	\
			map-drawing.c	\
			key-hook.c		\
			colors.c

OBJS	=	$(SRCS:.c=.o)

LIBFT_DIR	= libs/libft
LIBFT_BIN	= $(LIBFT_DIR)/libft.a

ifeq ($(IS_MACOS),Darwin)
	PLATFORM	= macos
	NAME		= fdf
	MLX_DIR		= libs/minilibx-macos
	MLX_BIN		= $(MLX_DIR)/libmlx.a

	CFLAGS		= 
	FRAMEWORKS	= -framework OpenGL -framework AppKit -lm
	LDFLAGS		= $(MLX_DIR) $(FRAMEWORKS)
endif

ifeq ($(IS_LINUX),Linux)
	PLATFORM	= linux
	NAME		= fdf
	MLX_DIR		= libs/minilibx-linux
	MLX_BIN		= $(MLX_DIR)/libmlx.a

	CFLAGS		=
	LDFLAGS		= $(MLX_DIR) -lX11 -lm
endif

ifndef PLATFORM
	$(error Unsupported platform)
endif


$(NAME): $(OBJS) libft mlx
	$(CC) $(OBJS) $(MLX_BIN) $(LIBFT_BIN) -o $(NAME) -I $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)


