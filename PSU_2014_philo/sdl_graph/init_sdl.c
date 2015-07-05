/*
** init_sdl.c for philo in /home/girard_r/rendu/PSU_2014_philo/sdl_graph
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Fri Feb 27 13:16:10 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 22:48:58 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include "philo.h"
#include "philo_sdl.h"

void		checkEvent()
{
  int		loop;
  SDL_Event	event;

  loop = 1;
  while (loop)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	loop = 0;
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	loop = 0;
    }
}

int		init_sdl()
{
  SDL_Surface	*window;

  XInitThreads();
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "Initialization SDL Error: %s\n", SDL_GetError());
      return 1;
    }
  if ((window = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE)) == NULL)
    {
      fprintf(stderr, "SDL Video Mode Error : %s\n", SDL_GetError());
      return 1;
    }
  get_window(1, window);
  SDL_WM_SetCaption("Be-Cleve in philosophy!", NULL);
  setBackground(window, 1);
  set_characters(window);
  SDL_Flip(window);
  return 0;
}

void		free_sdl()
{
  t_character	*characters;
  unsigned int	i;

  characters = get_characters(0, NULL);
  i = 0;
  setBackground(NULL, 0);
  while (i < 7)
    {
      SDL_FreeSurface(characters[i].dialog);
      SDL_FreeSurface(characters[i].state_img);
      SDL_FreeSurface(characters[i].char_img);
      SDL_FreeSurface(characters[i].rice_img);
      SDL_FreeSurface(characters[i].fill_img);
      i += 1;
    }
  SDL_FreeSurface(get_window(0, NULL));
  free(characters);
}

void		process_events()
{
  checkEvent();
  free_sdl();
  SDL_Quit();
}
