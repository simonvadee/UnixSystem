/*
** move.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 19:10:15 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 19:10:57 2015 Aurélien GIRARDEAU
*/

#include "includes.h"
#include "lemipc.h"

int		test_move(t_player *player, char **map, int x, int y)
{
  if (!is_taken(x, y, map))
    {
      map[player->y][player->x] = 0;
      map[y][x] = player->team;
      GUI_do(MOVE, player, x, y);
      player->y = y;
      player->x = x;
      return 1;
    }
  return 0;
}

int		second_choices(t_player *player, char **map, int left, int top)
{
  if (top == 0 && left != 0)
    {
      if (test_move(player, map, player->x + left, player->y + 1)
	  || test_move(player, map, player->x + left, player->y - 1))
	return 1;
    }
  else if (top != 0 && left == 0)
    {
      if (test_move(player, map, player->x + 1, player->y + top)
	  || test_move(player, map, player->x - 1, player->y + top))
	return 1;
    }
  else
    {
      if (test_move(player, map, player->x, player->y + top)
	  || test_move(player, map, player->x + left, player->y))
	return 1;
    }
  return 0;
}
