##
## Makefile for Makefile in /home/girard_r/rendu/cpp_abstractvm
## 
## Made by Aurélien GIRARDEAU
## Login   <girard_r@epitech.net>
## 
## Started on  Mon Feb 23 14:26:41 2015 Aurélien GIRARDEAU
## Last update Sun Mar  8 19:28:51 2015 Aurélien GIRARDEAU
##

NAME		=		lemipc

GUI		=		gui_lemipc

CC		=		gcc

RM		=		rm -f

INCL_DIR	=		includes/

SOURCE_DIR	=		sources

GUI_DIR		=		gui

CFLAGS		=		-Wall -Wextra -Werror -I./$(INCL_DIR) -g3

LDFLAGS		=		-lSDL

SRCS		=		$(SOURCE_DIR)/init_player.c \
				$(SOURCE_DIR)/init_ressources.c \
				$(SOURCE_DIR)/utils_ressources.c \
				$(SOURCE_DIR)/run_ia.c \
				$(SOURCE_DIR)/leader_functions.c \
				$(SOURCE_DIR)/follower_functions.c \
				$(SOURCE_DIR)/manage_death.c \
				$(SOURCE_DIR)/move.c \
				$(SOURCE_DIR)/end_process.c \
				$(SOURCE_DIR)/utils.c \
				$(SOURCE_DIR)/main.c

OBJS		=		$(SRCS:.c=.o)

SRCS_GUI	=		$(GUI_DIR)/init_sdl.c \
				$(GUI_DIR)/process_ipc.c \
				$(GUI_DIR)/player_actions.c \
				$(GUI_DIR)/utils.c

OBJS_GUI	=		$(SRCS_GUI:.c=.o)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

$(GUI):		$(OBJS_GUI)
		$(CC) -o $(GUI) $(OBJS_GUI) $(LDFLAGS)

all:		$(NAME) $(GUI)

clean:
		$(RM) $(OBJS) $(OBJS_GUI)

fclean:		clean
		$(RM) $(NAME) $(GUI)

re:		clean all

.PHONY:		all clean fclean re
