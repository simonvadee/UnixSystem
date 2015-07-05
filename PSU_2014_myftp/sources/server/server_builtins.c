/*
** server_builtins.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/server
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:24:08 2015 simon vadée
** Last update Sun Mar 22 10:24:09 2015 simon vadée
*/

#include "myftp.h"

e_errors	user_second(char **ret, int *size, int client_fd)
{
  char		*username;
  char		*passwd;

  username = get_next_line(client_fd);
  passwd = get_next_line(client_fd);
  if (!username
      || passwd
      || strcmp(username, "Anonymous") != 0)
    {
      *ret = strdup("Bad identification");
      *size = strlen("Bad identification") + 1;
    }
  else
    {
      *ret = strdup("Authentification successful");
      *size = strlen("Authentification successful") + 1;
    }
  return (USER);
}

char		*my_pwd(char *arg, int *size)
{
  char		*ret;

  (void)arg;
  ret = NULL;
  ret = getcwd(ret, 0);
  if (ret == NULL)
    {
      *size = strlen("'getcwd' failed so bad") + 1;
      ret = strdup("'getcwd' failed so bad");
    }
  *size = strlen(ret) + 1;
  return (ret);
}

char		*my_quit(char *arg, int *size)
{
  (void)arg;
  *size = QUIT;
  return (NULL);
}
