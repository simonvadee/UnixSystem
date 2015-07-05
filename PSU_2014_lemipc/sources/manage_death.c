/*
** manage_death.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 18:56:10 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:56:11 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include "includes.h"
#include "lemipc.h"

int		look_for_enemy(char team, int ***tab)
{
  int		i;

  i = 0;
  if (team == 0)
    return 0;
  while ((*tab)[i] != NULL)
    {
      if ((*tab)[i][0] == team)
	{
	  (*tab)[i][1] += 1;
	  return 0;
	}
      ++i;
    }
  if ((*tab = realloc(*tab, sizeof(int*) * (i + 2))) == NULL
      || ((*tab)[i] = malloc(sizeof(int) * 2)) == NULL)
    return -1;
  (*tab)[i][0] = team;
  (*tab)[i][1] = 1;
  (*tab)[i + 1] = NULL;
  return 0;
}

int		check_if_killed(int **tab, char team)
{
  int		i;

  i = 0;
  while (tab[i])
    {
      if (tab[i][1] >= 2 && tab[i][0] != team)
	{
	  free_tab(tab);
	  return 1;
	}
      ++i;
    }
  free_tab(tab);
  return 0;
}

int		process_death(t_player *player, char **map)
{
  if (player->is_lead)
    ultimate_whisper(player->team);
  map[player->y][player->x] = 0;
  GUI_do(DEAD, player, 0, 0);
  manage_ressources(UNLOCK);
  return 1;
}

int		is_dead(t_player *player, char **map)
{
  int		x;
  int		y;
  int		**tab;

  manage_ressources(LOCK);
  if ((tab = malloc(sizeof(int*))) == NULL)
    {
      manage_ressources(UNLOCK);
      return -1;
    }
  tab[0] = NULL;
  y = player->y - 2;
  while (++y <= player->y + 1)
    {
      x = player->x - 2;
      while (++x <= player->x + 1)
	{
	  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	    look_for_enemy(map[y][x], &tab);
	}
    }
  if (check_if_killed(tab, player->team))
    return (process_death(player, map));
  manage_ressources(UNLOCK);
  return 0;
}
