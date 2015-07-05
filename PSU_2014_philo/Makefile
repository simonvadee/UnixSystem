##
## Makefile for Makefile in /home/girard_r/rendu/cpp_abstractvm
## 
## Made by Aurélien GIRARDEAU
## Login   <girard_r@epitech.net>
## 
## Started on  Mon Feb 23 14:26:41 2015 Aurélien GIRARDEAU
## Last update Sun Mar  1 20:57:05 2015 Aurélien GIRARDEAU
##

NAME		=		philo

CC		=		gcc

RM		=		rm -f

INCL_DIR	=		includes/

SOURCE_DIR	=		sources

GUI_DIR		=		sdl_graph

CFLAGS		=		-I./$(INCL_DIR) -g3

LDFLAGS		=		-lpthread -lSDL -lSDL_image -lX11

SRCS		=		$(SOURCE_DIR)/share_chopsticks.c \
				$(GUI_DIR)/init_sdl.c \
				$(GUI_DIR)/process_sdl.c \
				$(GUI_DIR)/set_sdl.c \
				$(SOURCE_DIR)/manage_philo.c \
				$(SOURCE_DIR)/parse_entry.c \
				$(SOURCE_DIR)/main.c

OBJS		=		$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		clean all

.PHONY:		all clean fclean re
