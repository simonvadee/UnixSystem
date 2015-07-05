/*
** utils.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 18:56:29 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:56:30 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>

void            free_tab(int **tab)
{
  int           i;

  i = 0;
  while (tab[i])
    {
      free(tab[i]);
      i += 1;
    }
  free(tab);
}
