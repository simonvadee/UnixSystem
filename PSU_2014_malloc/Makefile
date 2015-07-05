##
## Makefile for Makefile in /home/girard_r/rendu/PSU_2014_malloc
## 
## Made by Aurélien GIRARDEAU
## Login   <girard_r@epitech.net>
## 
## Started on  Tue Jan 27 17:07:31 2015 Aurélien GIRARDEAU
## Last update Fri Feb  6 17:35:19 2015 Aurélien GIRARDEAU
##

SOURCE_DIR	=		./sources

INCLUDE_DIR	=		./includes

CC		=		gcc

CFLAGS		=		-fPIC -Wextra -Wall -Werror -I$(INCLUDE_DIR)

RM		=		rm -f

NAME		=		libmy_malloc_$(HOSTTYPE).so

LINK_NAME	=		libmy_malloc.so

SRCS_LIB	=		$(SOURCE_DIR)/header_utils.c \
				$(SOURCE_DIR)/my_malloc.c \
				$(SOURCE_DIR)/my_free.c \
				$(SOURCE_DIR)/my_realloc.c

OBJS_LIB	=		$(SRCS_LIB:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS_LIB)
		$(CC) -shared -o $(NAME) $(OBJS_LIB) -lpthread
		ln -sf $(NAME) $(LINK_NAME)

clean:
		$(RM) $(OBJS_LIB)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
