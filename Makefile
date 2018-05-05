##
## EPITECH PROJECT, 2017
## T3x3
## File description:
## Makefile
##

NAME	=	T3x3

CC	=	gcc

SRCDIR	=	src/
MAPDIR	=	$(SRCDIR)map/

SRC	=	$(SRCDIR)main.c \
		$(SRCDIR)menu.c \
		$(SRCDIR)game.c \
		$(SRCDIR)play.c \
		$(SRCDIR)ia.c \
		$(SRCDIR)evt_close.c \
		$(MAPDIR)map_create.c \
		$(MAPDIR)map_copy.c \
		$(MAPDIR)map_destroy.c \
		$(MAPDIR)map_aff.c \
		$(MAPDIR)map_swaps.c \
		$(MAPDIR)map_full.c \

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-I./include
CFLAGS	+=	-W -Wall -Wextra

LDFLAGS	+=	-l c_graph_prog

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
