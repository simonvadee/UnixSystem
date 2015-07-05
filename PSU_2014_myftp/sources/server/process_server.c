/*
** process_server.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/server
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:23:58 2015 simon vadée
** Last update Sun Mar 22 10:23:59 2015 simon vadée
*/

#include "myftp.h"

static const t_ptrf		g_struct_tab[8] =
  {
    {"user", &my_user},
    {"ls", &my_ls},
    {"cd", &my_cd},
    {"get", &my_get},
    {"put", &my_put},
    {"pwd", &my_pwd},
    {"quit", &my_quit},
    {NULL, NULL}
  };

void				call_function(char **ret, char *cmd,
					      char *arg, int *size)
{
  int				i;

  i = -1;
  while (g_struct_tab[++i].cmd)
    {
      if (strcmp(g_struct_tab[i].cmd, cmd) == 0)
	{
	  *ret = g_struct_tab[i].ptrf(arg, size);
	  break ;
	}
    }
  if (g_struct_tab[i].cmd == NULL)
    {
      *ret = strdup("Command not found");
      *size = strlen("Command not found") + 1;
    }
}

e_errors			manage_exceptions(char **ret, int *size,
						  int client_fd, char *arg)
{
  if (*size == QUIT)
    return (QUIT);
  else if (*size == USER)
    return (user_second(ret, size, client_fd));
  else if (*size == GET)
    return (get_second(ret, size, client_fd, arg));
  else if (*size == PUT)
    return (put_second(ret, size, client_fd, arg));
  return (OK);
}

e_errors			send_response(char **ret, int *size,
					      int client_fd, char *arg)
{
  if (!(*ret))
    {
      *size = strlen("Something bad happened") + 1;
      if (!(*ret = strdup("Something bad happened")))
	{
	  *size = -1;
	  write(client_fd, (char*)size, sizeof(int));
	  return (FAIL_MALLOC);
	}
    }
  write(client_fd, (char*)size, sizeof(int));
  write(client_fd, *ret, *size);
  if (arg)
    free(arg);
  if (*ret)
    free(*ret);
  return (OK);
}

e_errors			process_cmd(char *cmd, int client_fd)
{
  int				size;
  char				*arg;
  char				*ret;
  e_errors			error;

  arg = get_next_line(client_fd);
  if (arg && strlen(arg) == 0)
    {
      free(arg);
      arg = NULL;
    }
  call_function(&ret, cmd, arg, &size);
  if ((error = manage_exceptions(&ret, &size, client_fd, arg)) == QUIT
      || error > 0)
    {
      if (error == QUIT)
	{
	  write(client_fd, (char*)&size, sizeof(int));
	  return (QUIT);
	}
      handle_errors(error);
    }
  return (send_response(&ret, &size, client_fd, arg));
}

e_errors			handle_client(int client_fd,
					      char const *client_ip)
{
  char				*buff;
  e_errors			error;

  if (write(client_fd, "Connexion established, your IP adress is ", 41) == -1
      || write(client_fd, client_ip, strlen(client_ip)) == -1
      || write(client_fd, "\n", 1) == -1)
    return FAIL_WRITE;
  buff = NULL;
  while ((buff = get_next_line(client_fd)))
    {
      if (strlen(buff) > 0 && (error = process_cmd(buff, client_fd)))
    	return (error);
      free(buff);
    }
  if (close(client_fd) == -1)
    return (FAIL_CLOSE);
  return (OK);
}
