/*
** process_ipc.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/gui
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Thu Mar  5 16:39:36 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 19:28:19 2015 Aurélien GIRARDEAU
*/

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <strings.h>
#include "gui_lemipc.h"

static const t_cmd	g_cmd[5] =
  {
    {CREATE, &init_player},
    {MOVE, &move_player},
    {DEAD, &player_is_dead},
    {END, &end_gui},
    {0, NULL}
  };

int		check_command(e_cmd cmd)
{
  int		i;

  i = 0;
  while (g_cmd[i].ptrf != NULL)
    {
      if (g_cmd[i].type == cmd)
	return i;
      i += 1;
    }
  return -1;
}

void		process_ipc(SDL_Surface *window)
{
  key_t		key;
  int		msg_id;
  t_msg_gui	msgq;
  int		i;

  key = ftok("./", 0);
  if ((msg_id = msgget(key, SHM_R | SHM_W)) == -1)
    {
      msg_id = msgget(key, IPC_CREAT | SHM_R | SHM_W);
      printf("Created Msgq %d\n", msg_id);
    }
  bzero(&msgq, sizeof(msgq));
  while (msgrcv(msg_id, &msgq, sizeof(msgq), GUI_CHANNEL, IPC_NOWAIT))
    {
      if (checkEvent())
	return ;
      if (msg_id != -1 && (i = check_command(msgq.cmd)) != -1
	  && !g_cmd[i].ptrf(msgq, window))
	return ;
      SDL_Flip(window);
      bzero(&msgq, sizeof(msgq));
    }
}
