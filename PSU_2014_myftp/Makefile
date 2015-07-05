##
## Makefile for ftp in /home/vadee_s/PSU_2014_myftp
## 
## Made by simon vadée
## Login   <vadee_s@epitech.net>
## 
## Started on  Sun Mar 22 10:21:39 2015 simon vadée
## Last update Sun Mar 22 10:21:41 2015 simon vadée
##

CLIENT_DIR	=	sources/client

SERVER_DIR	=	sources/server

BOTH_DIR	=	sources/both

SRC_CLIENT	=	$(CLIENT_DIR)/main.c \
			$(CLIENT_DIR)/process_client.c \
			$(CLIENT_DIR)/client_builtins.c \
			$(BOTH_DIR)/get_next_line.c \
			$(BOTH_DIR)/error.c

SRC_SERVER	=	$(SERVER_DIR)/main.c \
			$(SERVER_DIR)/init_server.c \
			$(SERVER_DIR)/process_server.c \
			$(SERVER_DIR)/server_builtins.c \
			$(SERVER_DIR)/first_calls.c \
			$(SERVER_DIR)/get_put.c \
			$(SERVER_DIR)/ls_cd.c \
			$(BOTH_DIR)/get_next_line.c \
			$(BOTH_DIR)/security.c \
			$(BOTH_DIR)/error.c

OBJS_CLIENT	=	$(SRC_CLIENT:.c=.o)

OBJS_SERVER	=	$(SRC_SERVER:.c=.o)

CC		=	gcc

CFLAGS		=	-Wall -Wextra -Werror -I./includes/

CLIENT		=	client

SERVER		=	serveur


all:			$(SERVER) $(CLIENT)

$(SERVER):		$(OBJS_SERVER)
			$(CC) -o $(SERVER) $(OBJS_SERVER)

$(CLIENT):		$(OBJS_CLIENT)
			$(CC) -o $(CLIENT) $(OBJS_CLIENT)

clean:
			rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean:			clean
			rm -f $(SERVER) $(CLIENT)

re:			fclean all

.PHONY:			all clean fclean re

