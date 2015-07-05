/*
** gui_lemipc.h for gui in /home/girard_r/rendu/PSU_2014_lemipc/gui
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Wed Mar  4 16:58:03 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 17:17:48 2015 Aurélien GIRARDEAU
*/

#ifndef GUI_LEMIPC_H_
# define GUI_LEMIPC_H_

# include "includes.h"

# define S_WIDTH	900
# define S_HEIGHT	900
# define BPP		32

typedef struct	s_cmd
{
  e_cmd		type;
  int		(*ptrf)(t_msg_gui msgq, SDL_Surface *window);
}		t_cmd;

int	checkEvent();
void	set_background(SDL_Surface *window);
int	init_sdl();

int	init_player(t_msg_gui msgq, SDL_Surface *window);
int	move_player(t_msg_gui msgq, SDL_Surface *window);
int	player_is_dead(t_msg_gui msgq, SDL_Surface *window);
int	end_gui(t_msg_gui msgq, SDL_Surface *window);

void	process_ipc(SDL_Surface *window);
int	check_command(e_cmd cmd);

void	set_square(SDL_Rect *position, int color_hex,
		   SDL_Surface *window, char team);

#endif /* !GUI_LEMIPC_H_ */
