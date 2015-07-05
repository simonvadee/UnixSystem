/*
** main.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/client
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:24:36 2015 simon vadée
** Last update Sun Mar 22 10:24:36 2015 simon vadée
*/

#include <unistd.h>
#include "myftp.h"

int		secure_serv(char *current, char *path)
{
  static char	*root = NULL;
  char		*new;

  if (root == NULL)
    root = strdup(current);
  new = NULL;
  if (chdir(path) == -1)
    return (-1);
  new = getcwd(new, 0);
  if (strncmp(root, new, strlen(root)) != 0)
    {
      if (chdir(current) == -1)
	return (-1);
      return (-1);
    }
  if (chdir(current) == -1)
    return (-1);
  return (0);
}

int		secure_get(char *current, char *path)
{
  static char	*root = NULL;
  char		*new;
  char		*tmp;

  if (root == NULL)
    root = strdup(current);
  tmp = rindex(path, '/');
  *tmp = 0;
  new = NULL;
  if (chdir(path) == -1)
    return (-1);
  new = getcwd(new, 0);
  if (strncmp(root, new, strlen(root)) != 0)
    {
      if (chdir(current) == -1)
	return (-1);
      return (-1);
    }
  if (chdir(current) == -1)
    return (-1);
  return (0);
}
