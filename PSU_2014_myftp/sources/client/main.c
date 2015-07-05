/*
** main.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/client
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:24:36 2015 simon vadée
** Last update Sun Mar 22 10:24:36 2015 simon vadée
*/

#include "myftp.h"

int			main(int ac, char **av)
{
  int			socket_fd;
  e_errors		ret;

  if (ac != 3)
    {
      printf("Usage : ./client ip port");
      return 1;
    }
  if ((ret = init_client(av, &socket_fd))
      || (ret = client_loop(socket_fd)))
    {
      if (close(socket_fd) == -1)
	return 1;
      return handle_errors(ret);
    }
  if (close(socket_fd) == -1)
    return 1;
  return 0;
}
