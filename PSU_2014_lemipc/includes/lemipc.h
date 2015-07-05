/*
** lemipc.h for lemipc$ in /home/girard_r/rendu/PSU_2014_lemipc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Mar  8 18:57:54 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 19:31:23 2015 Aurélien GIRARDEAU
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

#include <sys/types.h>

# define NB_TEAMS 4

# define TEAM_CHANNEL(x) ((x) + 2)

# define TEAM_CHANNEL_DIE(x, y) ((x) + (y) + 2)

# define LOCK 0

# define UNLOCK 1

typedef enum
  {
    FIRST,
    OTHER
  }			e_case;

typedef struct		s_player
{
  int			x;
  int			y;
  char			is_lead;
  char			team;
}			t_player;

typedef struct		s_team_msg
{
  long			mtype;
  char			mtext;
}			t_team_msg;

typedef struct		s_target
{
  long			mtype;
  int			x;
  int			y;
}			t_target;

typedef struct		s_die
{
  long			mtype;
  char			lead;
}			t_die;

/*
** init_player.c
 */
void			determ_lead(t_player *player, char **map);
void			determ_team(t_player *player, e_case type);
void			determ_pos(t_player *player, char **map);
void			send_team_info(t_player *player);
t_player		*create_player(e_case type);

/*
** utils_ressources.c
*/
char			**get_map();
char			is_taken(int x, int y, char **map);
void			GUI_do(e_case cmd, t_player *player, int x, int y);
void			manage_ressources(int flag);

/*
** init_ressources.c
*/
int			create_map(key_t key);
int			init_ressources(e_case *type);

/*
** run_ia.c
*/
int			run(t_player *player);
void			hunt(t_player *player, t_target *target, char **map);
int			first_choice(t_player *player, int left, int top, char **map);
int			second_choices(t_player *player, char **map, int left, int top);

/*
** utils.c
*/
void			free_tab(int **tab);

/*
** manage_death.c
*/
int			look_for_enemy(char team, int ***tab);
int			check_if_killed(int **tab, char team);
int			is_dead(t_player *player, char **map);

/*
** leader_functions
*/
void			ultimate_whisper(char team);
void			lead_team(t_target *target, int nb_msg);
int			determ_target(t_target *target, t_player *player,
				      char **map, int cmp);
int			count_followers(char **map, char team);

/*
** follower_functions
*/
int			wannabe_lead(t_player *player);
int			listen_chief(t_target *target, char channel);

/*
** end_process.c
*/
int			remove_ressources();
int			stop_process(t_player *player, char **map);

/*
** move.c
*/
int			test_move(t_player *player, char **map, int x, int y);
int			second_choices(t_player *, char **, int, int);

#endif /* !LEMIPC_H_ */
