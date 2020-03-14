##
## EPITECH PROJECT, 2020
## for_norme
## File description:
## Makefile
##

NAME		=	T3x3

CC		=	g++

SRCDIR		=	Src/
GAMEDIR		=	$(SRCDIR)Game/
MENUDIR		=	$(SRCDIR)Menu/
BTNDIR		=	$(SRCDIR)Button/
UTYDIR		=	$(SRCDIR)Utility/
INCDIR		=	Include/

SRC		=	$(SRCDIR)Main.cpp \
			$(SRCDIR)Error.cpp \
			$(SRCDIR)Board.cpp \
			$(SRCDIR)SoundBox.cpp \
			$(GAMEDIR)Game.cpp \
			$(GAMEDIR)GameClassic.cpp \
			$(GAMEDIR)GameChallenge.cpp \
			$(GAMEDIR)GameEditor.cpp \
			$(MENUDIR)Menu.cpp \
			$(MENUDIR)MainMenu.cpp \
			$(MENUDIR)MenuClassic.cpp \
			$(MENUDIR)MenuChallenge.cpp \
			$(MENUDIR)MenuNbSwap.cpp \
			$(BTNDIR)Button.cpp \
			$(BTNDIR)ButtonText.cpp \
			$(BTNDIR)ButtonImage.cpp \
			$(BTNDIR)ButtonBoard.cpp \
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
