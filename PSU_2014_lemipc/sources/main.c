/*
** main.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 18:55:54 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:55:57 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <time.h>
#include "lemipc.h"

int		main()
{
  t_player	*player;
  e_case	type;

  srand(time(NULL));
  if (init_ressources(&type)
      || !(player = create_player(type)))
    return -1;
  run(player);
  free(player);
  return 0;
}
