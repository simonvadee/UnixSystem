/*
** utils.c for lemipc in /home/girard_r/rendu/PSU_2014_lemipc/gui
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Fri Mar  6 15:43:14 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 19:25:21 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "gui_lemipc.h"

void		set_square(SDL_Rect *position, int color_hex,
			   SDL_Surface *window, char team)
{
  SDL_Surface	*rect;
  int		r;
  int		g;
  int		b;

  r = ((color_hex >> 16) & 0xFF) - team * 100;
  g = ((color_hex >> 8) & 0xFF);
  b = (color_hex & 0xFF) + team * 100;

  rect = SDL_CreateRGBSurface(SDL_HWSURFACE, S_WIDTH / WIDTH,
				S_HEIGHT / HEIGHT, BPP, 0, 0, 0, 0);
  if (!team)
    SDL_FillRect(rect, NULL, SDL_MapRGB(window->format, r, g, b));
  else
    SDL_FillRect(rect, NULL, SDL_MapRGB(window->format, r, g, b));
  SDL_BlitSurface(rect, NULL, window, position);
  SDL_FreeSurface(rect);
}
