/*
** init_server.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/server
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Mar 22 10:23:25 2015 simon vadée
** Last update Sun Mar 22 10:23:26 2015 simon vadée
*/

#include "myftp.h"

e_errors		init_serv(char *param, int *socket_fd,
				  struct sockaddr_in *server_in, int *port)
{
  struct protoent	*pe;

  *port = atoi(param);
  if (!(pe = getprotobyname("TCP")))
    return (FAIL_GETPROTOBYNAME);
  if ((*socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (FAIL_SOCKET);
  server_in->sin_family = AF_INET;
  server_in->sin_port = htons(*port);
  server_in->sin_addr.s_addr = INADDR_ANY;
  if (bind(*socket_fd, (const struct sockaddr*)server_in, sizeof(*server_in))
      == -1)
    {
      if (close(*socket_fd) == -1)
	return (FAIL_CLOSE);
      return (FAIL_BIND);
    }
  if (listen(*socket_fd, SOMAXCONN) == -1)
    {
      if (close(*socket_fd) == -1)
	return (FAIL_CLOSE);
      return (FAIL_LISTEN);
    }
  return (OK);
}

e_errors		new_connection(int *client_fd, int socket_fd,
				       struct sockaddr_in *client_in,
				       socklen_t *client_in_size)
{
  bzero(client_in_size, sizeof(socklen_t));
  if ((*client_fd =
       accept(socket_fd, (struct sockaddr*)client_in, client_in_size)) == -1)
    {
      if (close(socket_fd) == -1)
	return (FAIL_CLOSE);
      return (FAIL_ACCEPT);
    }
  return (OK);
}

e_errors		main_loop(int socket_fd)
{
  struct sockaddr_in	client_in;
  socklen_t		client_in_size;
  int			client_fd;
  char			*client_ip;
  e_errors		ret;
  pid_t			pid;

  while (42)
    {
      if ((ret = new_connection(&client_fd, socket_fd,
				&client_in, &client_in_size)))
	return ret;
      if ((pid = fork()) == -1)
      	return (FAIL_FORK);
      if (pid == 0)
      	{
	  client_ip = inet_ntoa(client_in.sin_addr);
	  ret = handle_client(client_fd, client_ip);
     	  return (ret);
	}
      else if (pid > 0 && close(client_fd) == -1)
      	return (FAIL_CLOSE);
    }
  return (OK);
}
