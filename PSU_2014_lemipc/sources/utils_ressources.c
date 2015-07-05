/*
** utils_ressources.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 18:56:41 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:56:44 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "includes.h"
#include "lemipc.h"

char		**get_map()
{
  key_t	 	key;
  int		shm_id;
  void		*addr;
  char		*tmp;
  char		**map;
  int		i;
  int		j;

  j = -1;
  i = -1;
  if ((key = ftok("./", 0)) == -1
      || (map = malloc(sizeof(char*) * HEIGHT)) == NULL)
    return NULL;
  shm_id = shmget(key, WIDTH * HEIGHT, SHM_R | SHM_W);
  addr = shmat(shm_id, NULL, SHM_W);
  tmp = addr;
  while (++i != WIDTH * HEIGHT)
    {
      if ((i % WIDTH) == 0)
	{
	  ++j;
	  map[j] = tmp + WIDTH * j;
	}
    }
  return (map);
}

char		is_taken(int x, int y, char **map)
{
  if (x < WIDTH && y < HEIGHT)
    return (map[y][x]);
  return -1;
}

void		GUI_do(e_case cmd, t_player *player, int x, int y)
{
  key_t		key;
  int		msg_id;
  t_msg_gui	msg;

  if ((key = ftok("./", 0)) == -1)
    return;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(&msg, sizeof(t_msg_gui));
  msg.mtype = GUI_CHANNEL;
  msg.cmd = cmd;
  msg.coord_from[0] = player->x;
  msg.coord_from[1] = player->y;
  msg.coord_to[0] = x;
  msg.coord_to[1] = y;
  msg.team = player->team;
  msgsnd(msg_id, &msg, sizeof(t_msg_gui) - sizeof(long), 0);
}

void		manage_ressources(int flag)
{
  key_t		key;
  int		sem_id;
  struct sembuf	data;

  if ((key = ftok("./", 0)) == -1)
    return;
  sem_id = semget(key, 1, SHM_R | SHM_W);
  data.sem_num = 0;
  data.sem_flg = 0;
  data.sem_op = 1;
  if (flag == LOCK)
    data.sem_op = -1;
  semop(sem_id, &data, 0);
 }
