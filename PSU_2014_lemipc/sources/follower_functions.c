/*
** follower_functions.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Mar  8 18:55:06 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:55:09 2015 Aurélien GIRARDEAU
*/

#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include "includes.h"
#include "lemipc.h"

int		wannabe_lead(t_player *player)
{
  key_t		key;
  int		msg_id;
  t_die		die;

  if ((key = ftok("./", 0)) == -1)
    return 0;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(&die, sizeof(t_die));
  msgrcv(msg_id, &die, sizeof(t_die),
	 (long)(player->team + NB_TEAMS + 2), IPC_NOWAIT);
  if (die.lead)
    {
      player->is_lead = 1;
      return 1;
    }
  return 0;
}

int		listen_chief(t_target *target, char channel)
{
  key_t		key;
  int		msg_id;

  if ((key = ftok("./", 0)) == -1)
    return 1;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(target, sizeof(t_target));
  if (msgrcv(msg_id, target, sizeof(t_target),
	     (long)channel, IPC_NOWAIT) == -1)
    {
      target->x = WIDTH / 2;
      target->y = HEIGHT / 2;
    }
  if (target->x < 0)
    return 1;
  return 0;
}
