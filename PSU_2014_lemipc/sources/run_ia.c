/*
** run_ia.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Mar  8 16:12:19 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 19:10:51 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include "includes.h"
#include "lemipc.h"

int		first_choice(t_player *player, int left, int top, char **map)
{

  if (is_taken(player->x + left, player->y + top, map))
    return 0;
  map[player->y][player->x] = 0;
  map[player->y + top][player->x + left] = player->team;
  GUI_do(MOVE, player, player->x + left, player->y + top);
  player->x += left;
  player->y += top;
  return 1;
}

void		hunt(t_player *player, t_target *target, char **map)
{
  int		left;
  int		top;
  t_target	seek_target;
  static int	save = 0;

  if (determ_target(&seek_target, player, map, 1) == 1
      && seek_target.x == target->x
      && seek_target.y == target->y)
    return ;
  left = (target->x < player->x ? -1 : 1);
  left = (target->x == player->x ? 0 : left);
  top = (target->y < player->y ? -1 : 1);
  top = (target->y == player->y ? 0 : top);
  if (save == 1 || !first_choice(player, left, top, map))
    {
      if (save != 1)
	save = 2;
      save -= 1;
      second_choices(player, map, left, top);
    }
  return ;
}

int		handle_leader(t_player *player, char **map, t_target *target)
{
  int		ret;

  ret = 0;
  if (count_followers(map, player->team) >= 1 &&
      !(ret = determ_target(target, player, map, 1)))
    {
      stop_process(player, map);
      manage_ressources(UNLOCK);
      return 1;
    }
  if (ret > 0)
    {
      lead_team(target, count_followers(map, player->team));
      hunt(player, target, map);
    }
  return 0;
}

int		handle_followers(t_player *player, char **map, t_target *target)
{
  if (listen_chief(target, player->team + 2))
    {
      manage_ressources(UNLOCK);
      return 1;
    }
  if (wannabe_lead(player))
    {
      manage_ressources(UNLOCK);
      return 2;
    }
  hunt(player, target, map);
  return 0;
}

int		run(t_player *player)
{
  char		**map;
  t_target	target;
  int		ret;

  manage_ressources(LOCK);
  map = get_map();
  manage_ressources(UNLOCK);
  while (!is_dead(player, map))
    {
      manage_ressources(LOCK);
      if (player->is_lead && handle_leader(player, map, &target))
	break ;
      else if (!player->is_lead)
	{
	  if ((ret = handle_followers(player, map, &target)) == 1)
	    break ;
	  else if (ret == 2)
	    continue ;
	}
      manage_ressources(UNLOCK);
      usleep(100000);
    }
  shmdt(*map);
  free(map);
  return 0;
}
