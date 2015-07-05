/*
** player_actions.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  8 19:27:49 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 19:28:29 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <strings.h>
#include "gui_lemipc.h"

int		init_player(t_msg_gui msgq, SDL_Surface *window)
{
  SDL_Rect	position;

  position.x = msgq.coord_from[0] * S_WIDTH / WIDTH;
  position.y = msgq.coord_from[1] * S_HEIGHT / HEIGHT;
  set_square(&position, 0xFF0000, window, msgq.team);
  return 1;
}

int		end_gui(t_msg_gui msgq, SDL_Surface *window)
{
  (void)msgq;
  (void)window;
  return 0;
}

int		move_player(t_msg_gui msgq, SDL_Surface *window)
{
  SDL_Rect	position;

  position.x = msgq.coord_from[0] * S_WIDTH / WIDTH;
  position.y = msgq.coord_from[1] * S_HEIGHT / HEIGHT;
  set_square(&position, 0x000000, window, 0);

  position.x = msgq.coord_to[0] * S_WIDTH / WIDTH;
  position.y = msgq.coord_to[1] * S_HEIGHT / HEIGHT;
  set_square(&position, 0xFF0000, window, msgq.team);
  return 1;
}

int		player_is_dead(t_msg_gui msgq, SDL_Surface *window)
{
  SDL_Rect	position;

  position.x = msgq.coord_from[0] * S_WIDTH / WIDTH;
  position.y = msgq.coord_from[1] * S_HEIGHT / HEIGHT;
  set_square(&position, 0x000000, window, 0);
  return 1;
}
