/*
** init_ressources.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/sources
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Mar  8 18:55:34 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:55:36 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "includes.h"
#include "lemipc.h"

int		create_map(key_t key)
{
  int		shm_id;
  void		*addr;
  char		*map;
  int		i;

  i = 0;
  shm_id = shmget(key, WIDTH * HEIGHT, SHM_R | SHM_W | IPC_CREAT);
  if ((addr = shmat(shm_id, NULL, SHM_W)) == NULL)
    return -1;
  map = addr;
  while (i != WIDTH * HEIGHT)
    {
      map[i] = 0;
      ++i;
    }
  return (shmdt(addr));
}

int		init_ressources(e_case *type)
{
  key_t		key;
  int		sem_id;

  if ((key = ftok("./", 0)) == -1)
    return -1;
  *type = OTHER;
  usleep(1);
  if (shmget(key, WIDTH * HEIGHT, SHM_R | SHM_W) == -1)
    {
      *type = FIRST;
      if (create_map(key) == -1)
	return -1;
      sem_id = semget(key, 1, SHM_R | SHM_W | IPC_CREAT);
      semctl(sem_id, 0, SETVAL, 1);
      if (msgget(key, SHM_R | SHM_W) == -1)
	msgget(key, SHM_R | SHM_W | IPC_CREAT);
    }
  return 0;
}
