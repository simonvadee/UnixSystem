/*
** end_process.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 18:53:53 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:54:01 2015 Aurélien GIRARDEAU
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

int		remove_ressources()
{
  key_t		key;
  int		ipc_id;

  if ((key = ftok("./", 0)) == -1)
    return -1;
  ipc_id = msgget(key, SHM_R | SHM_W);
  msgctl(ipc_id, IPC_RMID, NULL);
  ipc_id = semget(key, 1, SHM_R | SHM_W);
  semctl(ipc_id, 0, IPC_RMID, 0);
  ipc_id = shmget(key, 10000, SHM_R | SHM_W);
  shmctl(ipc_id, IPC_RMID, NULL);
  return 0;
}

int		stop_process(t_player *player, char **map)
{
  key_t		key;
  int		msg_id;
  t_msg_gui	msgq;
  int		nb_follow;
  t_target	target;

  printf("TEAM %d WON\n", player->team);
  if ((key = ftok("./", 0)) == -1)
    return -1;
  msg_id = msgget(key, SHM_R | SHM_W);
  bzero(&msgq, sizeof(msgq));
  msgq.cmd = END;
  msgq.mtype = GUI_CHANNEL;
  msgsnd(msg_id, &msgq, sizeof(msgq) - sizeof(long), 0);
  nb_follow = count_followers(map, player->team);
  while (nb_follow--)
    {
      bzero(&target, sizeof(t_target));
      target.mtype = (long)(player->team + 2);
      target.x = -1;
      msgsnd(msg_id, &target, sizeof(t_target) - sizeof(long), 0);
      usleep(100);
    }
  sleep(1);
  return (remove_ressources());
}
