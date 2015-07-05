/*
** first_calls.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/server
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Mar 22 10:23:00 2015 simon vadée
** Last update Sun Mar 22 10:23:01 2015 simon vadée
*/

#include "myftp.h"

char		*my_user(char *arg, int *size)
{
  (void)arg;
  *size = USER;
  return NULL;
}

char		*my_get(char *arg, int *size)
{
  (void)arg;
  *size = GET;
  return (NULL);
}

char		*my_put(char *arg, int *size)
{
  (void)arg;
  *size = PUT;
  return (NULL);
}
