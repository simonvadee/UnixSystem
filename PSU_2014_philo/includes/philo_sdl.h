/*
** philo_sdl.h for philo_sdl.h in /home/girard_r/rendu/PSU_2014_philo/sdl_graph
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Fri Feb 27 13:28:14 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 22:45:46 2015 Aurélien GIRARDEAU
*/

#ifndef PHILO_SDL_H_
# define PHILO_SDL_H_

# include "philo.h"
# define WIDTH	1400
# define HEIGHT	720
# define BPP	32

typedef struct	s_character
{
  unsigned int	id;
  unsigned int	rice;
  SDL_Rect	position_char;
  SDL_Rect	position_state;
  SDL_Rect	position_dialog;
  SDL_Rect	position_rice;
  e_which	state;
  SDL_Surface	*dialog;
  SDL_Surface	*state_img;
  SDL_Surface	*char_img;
  SDL_Surface	*rice_img;
  SDL_Surface	*fill_img;
}		t_character;

typedef struct	s_state
{
  e_which	state;
  char		*path_img;
}		t_state;

t_character	*get_characters(int set, t_character *new_characters);
void		checkEvent();
SDL_Surface	*get_window(int set, SDL_Surface *new_window);
int		change_state(unsigned int id, e_which state);
t_character	*set_characters(SDL_Surface *window);
void		setBackground(SDL_Surface *window, char set);
int		init_sdl();
void		process_events();
SDL_Surface	*get_img_fromstate(e_which state);
void		process_rice(t_character **characters, unsigned int i);

#endif
