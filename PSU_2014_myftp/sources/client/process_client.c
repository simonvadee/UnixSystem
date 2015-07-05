/*
** process_client.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/client
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:24:53 2015 simon vadée
** Last update Sun Mar 22 10:24:54 2015 simon vadée
*/

#include "myftp.h"

e_errors		init_client(char **av, int *socket_fd)
{
  int			port;
  char			*ip;
  struct sockaddr_in	client_in;
  struct protoent	*pe;

  ip = av[1];
  port = atoi(av[2]);
  if (!(pe = getprotobyname("TCP")))
    return 1;
  if ((*socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return 1;
  client_in.sin_family = AF_INET;
  client_in.sin_port = htons(port);
  client_in.sin_addr.s_addr = inet_addr(ip);
  if (connect(*socket_fd,
	      (struct sockaddr*)&client_in, sizeof(client_in)) == -1)
    {
      if (close(*socket_fd) == -1)
	return FAIL_CLOSE;
      return FAIL_CONNECT;
    }
  return OK;
}

e_errors		write_socket(int socket_fd, char *cmd, char *arg)
{
  static int		i = 0;

  write(socket_fd, cmd, strlen(cmd));
  if (i++ == 0)
    write(socket_fd, "\n", 1);
  if (!arg)
    {
      arg = strdup("\n");
      write(socket_fd, arg, strlen(arg));
    }
  else
    {
      write(socket_fd, arg, strlen(arg));
      write(socket_fd, "\n", 1);
    }
  return OK;
}

e_errors       		send_cmd(char *buff, int socket_fd)
{
  char			*cmd;
  char			*arg;
  e_errors		error;

  if (!(cmd = strtok(buff, " ")) || cmd[0] == 10)
    return PASS;
  arg = strtok(NULL, "\n");
  if (!arg)
    {
      cmd[strlen(cmd) - 1] = 0;
      arg = NULL;
    }
  if ((strcmp(cmd, "put") == 0 && (error = my_put_client(arg, socket_fd)))
      || (strcmp(cmd, "user") == 0 && (error = my_user_client(socket_fd)))
      || (strcmp(cmd, "get") == 0 && (error = my_get_client(arg, socket_fd)))
      || (strcmp(cmd, "quit") == 0 && (error = QUIT)))
    return error;
  else
    return write_socket(socket_fd, cmd, arg);
}

e_errors		transfert_data(char *buff, int socket_fd)
{
  char			*rd;
  int			size;
  e_errors		error;

  size = 0;
  rd = NULL;
  if ((error = send_cmd(buff, socket_fd)) == QUIT
      || error == PASS)
    return error;
  read(socket_fd, (char*)&size, sizeof(int));
  if (size < 0
      || !(rd = malloc(size)))
    return FAIL_MALLOC;
  read(socket_fd, rd, size);
  rd[size - 1] = 0;
  write(1, rd, strlen(rd));
  write(1, "\n", 1);
  free(rd);
  return OK;
}

e_errors		client_loop(int socket_fd)
{
  char			*buff;
  e_errors		error;
  size_t		ret;

  ret = 0;
  error = OK;
  buff = get_next_line(socket_fd);
  printf("%s\n", buff);
  free(buff);
  buff = NULL;
  write(1, "$> ", 3);
  while (getline(&buff, &ret, stdin) > 0)
    {
      error = transfert_data(buff, socket_fd);
      if (error > 0 || error == QUIT)
	return error;
      write(1, "$> ", 3);
    }
  return OK;
}
