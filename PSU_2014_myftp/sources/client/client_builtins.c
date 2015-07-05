/*
** client_builtins.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/client
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:24:27 2015 simon vadée
** Last update Sun Mar 22 10:24:28 2015 simon vadée
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "myftp.h"

e_errors		my_user_client(int socket_fd)
{
  char			*username;
  char			*passwd;
  static int		i = 0;

  write(socket_fd, "user", 4);
  if (i++ == 0)
    write(socket_fd, "\n", 1);
  write(socket_fd, "\n", 1);
  write(1, "please enter a username : ", 26);
  if (!(username = get_next_line(0)))
    write(socket_fd, "\n", 1);
  else
    {
      write(socket_fd, username, strlen(username));
      write(socket_fd, "\n", 1);
    }
  write(1, "please enter a password : ", 26);
  if (!(passwd = get_next_line(0)))
    write(socket_fd, "\n", 1);
  else
    {
      write(socket_fd, passwd, strlen(passwd));
      write(socket_fd, "\n", 1);
    }
  return (USER);
}

e_errors		my_put_client(char *arg, int socket_fd)
{
  (void)arg;
  (void)socket_fd;
  return (PUT);
}

e_errors		get_client_aux(int socket_fd, char *arg)
{
  char			*buff;
  int			size;
  int			fd_arg;

  read(socket_fd, &size, sizeof(int));
  if (size == -1)
    return (GET);
  else if ((fd_arg = open(arg, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    return (FAIL_OPEN);
  else if (!(buff = malloc(size)))
    return (FAIL_MALLOC);
  read(socket_fd, buff, size);
  write(fd_arg, buff, size);
  write(fd_arg, "\n", 1);
  close(fd_arg);
  return (GET);
}

e_errors		my_get_client(char *arg, int socket_fd)
{
  static int		i = 0;

  write(socket_fd, "get", 3);
  if (i++ == 0)
    write(socket_fd, "\n", 1);
  if (arg)
    {
      write(socket_fd, arg, strlen(arg));
      write(socket_fd, "\n", 1);
    }
  else
    {
      write(socket_fd, "\n", 1);
      return (GET);
    }
  return (get_client_aux(socket_fd, arg));
}
