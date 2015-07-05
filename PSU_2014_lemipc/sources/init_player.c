/*
** init_player.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Mar  8 18:55:24 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:55:26 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include "includes.h"
#include "lemipc.h"

void		determ_lead(t_player *player, char **map)
{
  int		x;
  int		y;

  y = 0;
  while (y != HEIGHT)
    {
      x = 0;
      while (x != WIDTH)
  	{
  	  if (map[y][x] == player->team)
  	    {
  	      player->is_lead = 0;
  	      return ;
  	    }
  	  ++x;
  	}
      ++y;
    }
  player->is_lead = 1;
}

void		determ_team(t_player *player, e_case type)
{
  key_t		key;
  int		msg_id;
  t_team_msg	team;

  if (type == FIRST)
    {
      player->team = 1;
      return ;
    }
  if ((key = ftok("./", 0)) == -1)
    return;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(&team, sizeof(t_team_msg));
  msgrcv(msg_id, &team, sizeof(t_team_msg), DEFINE_TEAM_CHANNEL, 0);
  player->team = team.mtext % (NB_TEAMS + 1);
  player->team = (player->team == 0) ? 1 : player->team;
}

void		determ_pos(t_player *player, char **map)
{
  usleep(10000);
  player->x = random() % WIDTH;
  player->y = random() % HEIGHT;
  while (is_taken(player->x, player->y, map))
    {
      player->x = random() % WIDTH;
      player->y = random() % HEIGHT;
    }
  map[player->y][player->x] = player->team;
}

void		send_team_info(t_player *player)
{
  key_t		key;
  int		msg_id;
  t_team_msg	team;

  if ((key = ftok("./", 0)) == -1)
    return;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(&team, sizeof(t_team_msg));
  team.mtype = DEFINE_TEAM_CHANNEL;
  team.mtext = player->team + 1;
  msgsnd(msg_id, &team, sizeof(char), 0);
}

t_player	*create_player(e_case type)
{
  t_player	*player;
  char		**map;

  manage_ressources(LOCK);
  if ((player = malloc(sizeof(t_player))) == NULL
      || (map = get_map()) == NULL)
    return NULL;
  determ_team(player, type);
  determ_lead(player, map);
  determ_pos(player, map);
  GUI_do(CREATE, player, 0, 0);
  send_team_info(player);
  free(map);
  shmdt(map);
  manage_ressources(UNLOCK);
  return (player);
}
