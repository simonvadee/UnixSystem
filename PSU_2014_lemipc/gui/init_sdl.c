/*
** init_sdl.c<2> for gui_sdl in /home/girard_r/rendu/PSU_2014_lemipc/gui
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Wed Mar  4 16:49:59 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 16:56:30 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "gui_lemipc.h"

int		checkEvent()
{
  SDL_Event	event;

  if (SDL_PollEvent(&event))
    {
      if ((event.type == SDL_QUIT)
	  || (event.type == SDL_KEYDOWN
	      && event.key.keysym.sym == SDLK_ESCAPE))
	return 1;
    }
  return 0;
}

void		set_background(SDL_Surface *window)
{
  SDL_Surface	*background;
  SDL_Rect	position;

  position.x = 0;
  position.y = 0;
  background = SDL_CreateRGBSurface(SDL_HWSURFACE, S_WIDTH, S_HEIGHT, BPP,
				    0, 0, 0, 0);
  SDL_FillRect(background, NULL, SDL_MapRGB(window->format, 0, 0, 0));
  SDL_BlitSurface(background, NULL, window, &position);
  SDL_FreeSurface(background);
}

int		init_sdl()
{
  SDL_Surface	*window;

  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "Initialization SDL Error: %s\n", SDL_GetError());
      return 1;
    }
  if ((window = SDL_SetVideoMode(S_WIDTH, S_HEIGHT, BPP, SDL_HWSURFACE))
      == NULL)
    {
      fprintf(stderr, "SDL Video Mode Error : %s\n", SDL_GetError());
      return 1;
    }
  SDL_WM_SetCaption("lemipc", NULL);
  set_background(window);
  SDL_Flip(window);
  process_ipc(window);
  SDL_FreeSurface(window);
  return 0;
}

int		main()
{
  if (!init_sdl())
    return 1;
  checkEvent();
  SDL_Quit();
  return 0;
}
