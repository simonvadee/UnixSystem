/*
** get_next_line.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/both
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Mar 22 10:22:42 2015 simon vadée
** Last update Sun Mar 22 10:22:45 2015 simon vadée
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "myftp.h"

int		my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != 0)
    i = i + 1;
  return (i);
}

char		*my_strcat(char *dest, char *src)
{
  int		i;
  int		j;

  j = 0;
  i = my_strlen(dest);
  while (src[j])
    {
      dest[i] = src[j];
      i = i + 1;
      j = j + 1;
    }
  dest[i] = 0;
  return (dest);
}

char            *my_realloc(char *src, int ret)
{
  char          *dest;

  if (ret == 0)
    return (src);
  dest = malloc((my_strlen(src) + ret + 1) * sizeof(char));
  if (dest == NULL)
    return (NULL);
  *dest = 0;
  my_strcat(dest, src);
  free(src);
  return (dest);
}

int             stack_buffer(char *buffer, char *tmp)
{
  int           j;

  j = 0;
  while (tmp[j] != 0)
    {
      if (tmp[j] == '\n')
        {
          tmp[j] = 0;
          *buffer = 0;
	  my_strcat(buffer, &tmp[j + 1]);
          return (0);
        }
      j = j + 1;
    }
  *buffer = 0;
  return (1);
}

char            *get_next_line(const int fd)
{
  static char   buffer[BUFFER];
  char          *tmp;
  int           ret;

  tmp = malloc(BUFFER * sizeof(char));
  if (tmp == NULL || fd < 0)
    return (NULL);
  *tmp = 0;
  my_strcat(tmp, buffer);
  *buffer = 0;
  ret = BUFFER;
  while (stack_buffer(buffer, tmp) != 0 && ret == BUFFER)
    {
      ret = read(fd, buffer, BUFFER);
      if (ret == - 1)
        return (NULL);
      buffer[ret] = 0;
      tmp = my_realloc(tmp, ret);
      my_strcat(tmp, buffer);
    }
  if (*tmp == 0 && my_strlen(buffer) == 0 && ret != BUFFER)
    return (NULL);
  return (tmp);
}
