/*
** leader_functions.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 18:55:44 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:55:45 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include "includes.h"
#include "lemipc.h"

void		ultimate_whisper(char team)
{
  key_t		key;
  int		msg_id;
  t_die		die;

  if ((key = ftok("./", 0)) == -1)
    return ;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(&die, sizeof(t_die));
  die.mtype = (long)(team + NB_TEAMS + 2);
  die.lead = 1;
  msgsnd(msg_id, &die, sizeof(t_die) - sizeof(long), 0);
}

void		lead_team(t_target *target, int nb_msg)
{
  key_t		key;
  int		msg_id;

  if ((key = ftok("./", 0)) == -1)
    return ;
  msg_id = msgget(key, SHM_R | SHM_W);
  while (nb_msg-- > 0)
    {
      msgsnd(msg_id, target, sizeof(t_target) - sizeof(long), 0);
      usleep(100);
    }
}

void		incr_y(int cmp, int *to_incr, int x, t_player *player)
{
  *to_incr = *to_incr + 1;
  while (x > player->x - cmp && x < player->x + cmp
	 && *to_incr > player->y - cmp && *to_incr < player->y + cmp)
    *to_incr = *to_incr + 1;
}

int		determ_target(t_target *target, t_player *player,
			      char **map, int cmp)
{
  int		y;
  int		x;

  if (cmp >= WIDTH && cmp >= HEIGHT)
    return 0;
  x = player->x - cmp - 1;
  while (++x <= player->x + cmp)
    {
      y = player->y - cmp;
      while (y <= player->y + cmp)
	{
	  if (y >= 0 && y < HEIGHT
	      && x >= 0 && x < WIDTH
	      && map[y][x] != 0 && map[y][x] != player->team)
	    {
	      bzero(target, sizeof(t_target));
	      target->x = x;
	      target->y = y;
	      target->mtype = (long)(player->team + 2);
	      return cmp;
	    }
	  incr_y(cmp, &y, x, player);
	}
    }
  return (determ_target(target, player, map, cmp + 1));
}

int		count_followers(char **map, char team)
{
  int		count;
  int		y;
  int		x;

  x = 0;
  count = 0;
  while (x != WIDTH)
    {
      y = 0;
      while (y != HEIGHT)
	{
	  if (map[y][x] == team)
	    ++count;
	  ++y;
	}
      ++x;
    }
  return (count - 1);
}
