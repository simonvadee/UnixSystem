/*
** myftp.h for ftp in /home/vadee_s/PSU_2014_myftp/includes
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:21:21 2015 simon vadée
** Last update Sun Mar 22 10:21:24 2015 simon vadée
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define BUFFER 1024

typedef enum
  {
    PASS = -5,
    GET,
    USER,
    PUT,
    QUIT,
    OK,
    FAIL_CLOSE,
    FAIL_LISTEN,
    FAIL_BIND,
    FAIL_GETPROTOBYNAME,
    FAIL_SOCKET,
    FAIL_ACCEPT,
    FAIL_CONNECT,
    FAIL_MALLOC,
    FAIL_FORK,
    FAIL_WRITE,
    FAIL_READ,
    FAIL_FSTAT,
    FAIL_OPEN
  }	e_errors;

typedef struct		s_ptrf
{
  char			*cmd;
  char			*(*ptrf)(char *, int *);
}			t_ptrf;

typedef struct		s_error
{
  e_errors		error;
  char			*msg;
}			t_error;

char			*get_next_line(const int fd);
e_errors		handle_client(int client_fd, char const *client_ip);
e_errors		init_serv(char *param, int *socket_fd,
				  struct sockaddr_in *server_in, int *port);
int			handle_errors(e_errors error);
e_errors		main_loop(int socket_fd);
e_errors		client_loop(int socket_fd);
e_errors		init_client(char **av, int *socket_fd);

e_errors		my_user_client(int socket_fd);
e_errors		my_put_client(char *arg, int socket_fd);
e_errors		my_get_client(char *arg, int socket_fd);

char			*my_user(char *arg, int *size);
char			*my_ls(char *arg, int *size);
char			*my_cd(char *arg, int *size);
char			*my_get(char *arg, int *size);
char			*my_put(char *arg, int *size);
char			*my_pwd(char *arg, int *size);
char			*my_quit(char *arg, int *size);
e_errors		user_second(char **ret, int *size, int client_fd);
e_errors		put_second(char **ret, int *size,
				   int client_fd, char *arg);
e_errors		get_second(char **ret, int *size,
				   int client_fd, char *arg);

int			secure_serv(char *current, char *path);
int			secure_get(char *current, char *path);

#endif /* !CLIENT_H_ */
