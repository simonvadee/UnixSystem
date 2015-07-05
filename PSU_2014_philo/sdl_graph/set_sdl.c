/*
** set_sdl.c for philo in /home/girard_r/rendu/PSU_2014_philo/sdl_graph
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 20:54:43 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 22:44:21 2015 Aurélien GIRARDEAU
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include "philo.h"
#include "philo_sdl.h"

static const char	g_img_names[7][50] =
  {
    {"sdl_graph/Cleveland/Cleveland_Brown.png"},
    {"sdl_graph/Cleveland/dog.png"},
    {"sdl_graph/Cleveland/Donna.png"},
    {"sdl_graph/Cleveland/Junior.png"},
    {"sdl_graph/Cleveland/Rallo.png"},
    {"sdl_graph/Cleveland/Roberta.png"},
    {"sdl_graph/Cleveland/Tim_the_bear.png"}
  };

void		set_rice(t_character **characters, SDL_Surface *window)
{
  unsigned int	i;

  i = 0;
  while (i < 7)
    {
      (*characters)[i].position_rice.x = (*characters)[i].position_char.x
	+ ((*characters)[i].char_img)->w / 2 + 10;
      (*characters)[i].position_rice.y = 50;
      (*characters)[i].rice_img = SDL_CreateRGBSurface(SDL_HWSURFACE, 100,
						       25, BPP, 0, 0, 0, 0);
      SDL_FillRect((*characters)[i].rice_img, NULL,
		   SDL_MapRGB(window->format, 156, 60, 70));
      SDL_BlitSurface((*characters)[i].rice_img, NULL, window,
		      &(*characters)[i].position_rice);
      i += 1;
    }
}

void		set_char_pos(t_character **characters)
{
  int		gap = 20;
  unsigned int	i;

  i = 0;
  while (i < 7)
    {
      (*characters)[i].id = i;
      if (i == 1)
	(*characters)[i].position_char.x = gap + 40;
      else if (i == 4)
	(*characters)[i].position_char.x = gap + 50;
      else
	(*characters)[i].position_char.x = gap;
      (*characters)[i].position_state.y = HEIGHT * 1/3 - 100;
      gap = gap + 175;
      (*characters)[i].position_char.y = HEIGHT * 1/2;
      (*characters)[i].state = REST;
      (*characters)[i].char_img = IMG_Load(g_img_names[i]);
      (*characters)[i].position_state.x = (*characters)[i].position_char.x
	+ ((*characters)[i].char_img)->w / 2 + 10;
      i += 1;
    }
}

t_character	*set_characters(SDL_Surface *window)
{
  t_character	*characters;
  unsigned int	i;

  i = 0;
  if ((characters = malloc(sizeof(t_character) * 7)) == NULL)
    return NULL;
  set_char_pos(&characters);
  set_rice(&characters, window);
  while (i < 7)
    {
      characters[i].dialog = IMG_Load("sdl_graph/Cleveland/bulle.png");
      characters[i].state_img = IMG_Load("sdl_graph/Cleveland/zzz.png");
      characters[i].position_dialog.x = characters[i].position_state.x - 70;
      characters[i].position_dialog.y = characters[i].position_state.y - 40;
      characters[i].rice = 10;
      SDL_BlitSurface(characters[i].char_img, NULL, window,
		      &(characters[i].position_char));
      SDL_BlitSurface(characters[i].dialog, NULL, window,
		      &characters[i].position_dialog);
      SDL_BlitSurface(characters[i].state_img, NULL, window,
		      &(characters[i].position_state));
      i += 1;
    }
  return (get_characters(1, characters));
}

void			setBackground(SDL_Surface *window, char set)
{
  static SDL_Surface	*background = NULL;
  SDL_Rect		position_back;

  if (set == 0)
    {
      SDL_FreeSurface(background);
      return ;
    }
  position_back.x = 0;
  position_back.y = 0;
  background = IMG_Load("sdl_graph/Cleveland/background_cleveland.png");
  SDL_BlitSurface(background, NULL, window, &position_back);
}
