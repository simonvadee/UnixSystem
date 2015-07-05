/*
** get_put.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/server
**
** Made by simon vadée
** Login   <vadee_s@epitech.net>
**
** Started on  Sun Mar 22 10:23:13 2015 simon vadée
** Last update Sun Mar 22 10:23:15 2015 simon vadée
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "myftp.h"

e_errors	put_second(char **ret, int *size, int client_fd, char *arg)
{
  (void)ret;
  (void)size;
  (void)client_fd;
  (void)arg;
  return (PUT);
}

e_errors		send_file(char **ret, int *size, int client_fd, int file_d)
{
  struct stat	buf;
  char		*buff;

  if (fstat(file_d, &buf) == -1)
    return (FAIL_FSTAT);
  write(client_fd, &(buf.st_size), sizeof(int));
  if (!(buff = malloc(buf.st_size)))
    return (FAIL_MALLOC);
  else if (read(file_d, buff, buf.st_size) <= 0)
    return (FAIL_READ);
  close(file_d);
  write(client_fd, buff, buf.st_size);
  *ret = strdup("File downoald complete");
  *size = strlen("File downoald complete") + 1;
  return (GET);
}
e_errors	get_second(char **ret, int *size, int client_fd, char *arg)
{
  int		file_d;
  int		tmp;

  tmp = -1;
  *ret = NULL;
  if (!arg)
    {
      *ret = strdup("'get' needs an argument");
      *size = strlen("'get' needs an argument") + 1;
      return (GET);
    }
  if ((file_d = open(arg, O_RDWR, S_IRUSR | S_IWUSR)) == -1
      || secure_get(getcwd(*ret, 0), arg) == -1)
    {
      *ret = strdup("Failed to open file");
      *size = strlen("Failed to open file") + 1;
      write(client_fd, &tmp, sizeof(int));
      close(file_d);
      return (GET);
    }
  else
    return (send_file(ret, size, client_fd, file_d));
}
