/*
** ls_cd.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/server
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:23:37 2015 simon vadée
** Last update Sun Mar 22 10:23:38 2015 simon vadée
*/

#include <dirent.h>
#include "myftp.h"

char		*ls_aux(char **ret, int *size, struct dirent *dir_infos)
{
  *size = (*ret == NULL ? 0 : strlen(*ret));
  if (!(*ret) && !(*ret = calloc(sizeof(char), strlen(dir_infos->d_name) + 2)))
    return (NULL);
  else if (!(*ret =
	     realloc(*ret, (size_t)(strlen(dir_infos->d_name) + *size + 2))))
    return (NULL);
  *ret = strcat(*ret, dir_infos->d_name);
  *ret = strcat(*ret, "\n");
  return (*ret);
}

char		*my_ls(char *arg, int *size)
{
  char		*dir_name;
  DIR		*dir;
  struct dirent	*dir_infos;
  char		*ret;

  ret = NULL;
  dir_name = (arg == NULL ? "." : arg);
  if (secure_serv(getcwd(ret, 0), dir_name) == -1)
    {
      *size = strlen("You do not have permission to go there") + 1;
      return (strdup("You do not have permission to go there"));
    }
  else if ((dir = opendir(dir_name)) == NULL)
    {
      *size = strlen("System error : 'opendir' failed") + 1;
      return (strdup("System error : 'opendir' failed"));
    }
  while ((dir_infos = readdir(dir)) != NULL)
    {
      if (!ls_aux(&ret, size, dir_infos))
	return (NULL);
    }
  ret[strlen(ret) - 3] = 0;
  closedir(dir);
  return (ret);
}

char		*my_cd(char *arg, int *size)
{
  char		*dir_name;
  char		*ret;

  ret = NULL;
  dir_name = (arg == NULL ? "." : arg);
  if (secure_serv(getcwd(ret, 0), dir_name) == -1)
    {
      *size = strlen("You do not have permission to go there") + 1;
      return (strdup("You do not have permission to go there"));
    }
  else if (chdir(dir_name) == -1)
    {
      *size = strlen("System error : 'chdir' failed") + 1;
      return (strdup("System error : 'chdir' failed"));
    }
  if ((ret = strdup("current directory moved to ")) == NULL
      || (ret = realloc(ret, strlen(ret) + strlen(dir_name) + 1)) == NULL)
    return (NULL);
  ret = strcat(ret, dir_name);
  *size = strlen(ret) + 1;
  return (ret);
}
