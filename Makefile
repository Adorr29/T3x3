##
## EPITECH PROJECT, 2018
## for_norme
## File description:
## Makefile
##

NAME		=	T3x3

CC		=	g++

SRCDIR		=	Src/
GAMDIR		=	$(SRCDIR)Game/
UTYDIR		=	$(SRCDIR)Utility/
INCDIR		=	Include/

SRC		=	$(SRCDIR)Main.cpp \
			$(SRCDIR)Error.cpp \
			$(SRCDIR)Board.cpp \
			$(GAMDIR)Game.cpp \
			$(GAMDIR)GameFillBoard.cpp \
			$(UTYDIR)Globpp.cpp \
			$(UTYDIR)Split.cpp \

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	+=	-I $(INCDIR)
CXXFLAGS	+=	-W -Wall -Wextra

LDFLAGS		+=	-l sfml-system
LDFLAGS		+=	-l sfml-window
LDFLAGS		+=	-l sfml-graphics
LDFLAGS		+=	-l sfml-audio

%.o		:	%.cpp
			@$(CC) -c -o $@ $< $(CXXFLAGS)

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean		:
			@rm -f $(OBJ)

fclean		:	clean
			@rm -f $(NAME)

re		:	fclean all

debug		:	CXXFLAGS += -g3
debug		:	re
