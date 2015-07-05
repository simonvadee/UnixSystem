/*
** philo.h for philo in /home/girard_r/rendu/PSU_2014_philo
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 19:47:34 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 19:49:29 2015 Aurélien GIRARDEAU
*/

#ifndef PHILO_H_
# define PHILO_H_

# define TRUE 1

# define FALSE 0

#include <pthread.h>

typedef enum
  {
    EAT,
    THINK,
    REST
  } e_state;

typedef enum
  {
    NONE,
    LEFT,
    RIGHT,
    BOTH
  } e_which;

typedef struct		s_chopstick
{
  unsigned int		id;
  pthread_mutex_t	handler;
}			t_chopstick;

typedef struct		s_information
{
  unsigned int		nb_philo;
  unsigned int		rice;
  unsigned int		time_eating;
  unsigned int		time_thinking;
}			t_infos;

typedef struct		s_philosopher
{
  unsigned int		id;
  e_state		state;
  int			rice;
  pthread_t		instance;

  t_chopstick		*tab;
  t_infos		*data;

  e_which		which;
}			t_philosopher;

int			set_informations(t_chopstick **sticks, t_philosopher **philo, t_infos *data);
int			default_settings(t_chopstick **sticks, t_philosopher **philo);
int			ask_questions(t_infos *data, char *buff);
int			custom_settings(t_chopstick **sticks, t_philosopher **philo);
int			parse_entry(t_chopstick **sticks, t_philosopher **philo);

void			eat(t_philosopher *philo, char display);
void			think(t_philosopher *philo, char display);
void			rest(t_philosopher *philo, char display);
void			*philo_routine(void*);

void			take_chopstick(t_philosopher *philo, t_chopstick *stick);
void			check_neighboors(t_philosopher *philo);
void			look_for_chopsticks(t_philosopher *philo);
char			get_graph(int set);

#endif /* !PHILO_H_ */
