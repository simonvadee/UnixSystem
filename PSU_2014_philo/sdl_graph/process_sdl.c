/*
** process_sdl.c for philo in /home/girard_r/rendu/PSU_2014_philo/sdl_graph
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 20:49:08 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 22:16:10 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include "philo.h"
#include "philo_sdl.h"

static const t_state	g_getfromstate[3] =
  {
    {EAT, "sdl_graph/Cleveland/bol_riz.png"},
    {THINK, "sdl_graph/Cleveland/think.png"},
    {REST, "sdl_graph/Cleveland/zzz.png"}
  };

t_character		*get_characters(int set, t_character *new_characters)
{
  static t_character	*characters;

  if (set == 1)
    characters = new_characters;
  return (characters);
}

SDL_Surface		*get_window(int set, SDL_Surface *new_window)
{
  static SDL_Surface	*window;

  if (set == 1)
    window = new_window;
  return (window);
}

SDL_Surface		*get_img_fromstate(e_which state)
{
  SDL_Surface		*to_return;
  unsigned int		i;

  i = 0;
  to_return = NULL;
  while (i < 3)
    {
      if (g_getfromstate[i].state == state)
	to_return = IMG_Load(g_getfromstate[i].path_img);
      i += 1;
    }
  return (to_return);
}

void			process_rice(t_character **characters, unsigned int i)
{
  SDL_Surface		*window;

  window = get_window(0, NULL);
  if ((*characters)[i].rice == 0)
    return ;
  if ((*characters)[i].rice < 10)
    SDL_FreeSurface((*characters)[i].fill_img);
  (*characters)[i].rice -= 1;
  (*characters)[i].fill_img = SDL_CreateRGBSurface(SDL_HWSURFACE,
						   10 * (*characters)[i].rice,
						   25, BPP, 0, 0, 0, 0);
  SDL_FillRect((*characters)[i].fill_img, NULL,
	       SDL_MapRGB(window->format, 156, 50, 70));
  SDL_FillRect((*characters)[i].rice_img, NULL,
  	       SDL_MapRGB(window->format, 0, 0, 0));
  SDL_BlitSurface((*characters)[i].rice_img, NULL, window,
		  &(*characters)[i].position_rice);
  SDL_BlitSurface((*characters)[i].fill_img, NULL, window,
		  &(*characters)[i].position_rice);
}

int			change_state(unsigned int id, e_which state)
{
  t_character		*characters;
  unsigned int		i;

  i = 0;
  characters = get_characters(0, NULL);
  while (i < 7)
    {
      if (characters[i].id == id)
	{
	  if (state == EAT)
	    process_rice(&characters, i);
	  SDL_BlitSurface(characters[i].dialog, NULL, get_window(0, NULL),
			  &characters[i].position_dialog);
	  SDL_FreeSurface(characters[i].state_img);
	  characters[i].state_img = get_img_fromstate(state);
	  SDL_BlitSurface(characters[i].state_img, NULL,
			  get_window(0, NULL), &(characters[i].position_state));
	}
      i += 1;
    }
  SDL_Flip(get_window(0, NULL));
  return 0;
}
