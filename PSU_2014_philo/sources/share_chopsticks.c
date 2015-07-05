/*
** share_chopsticks.c for philo in /home/girard_r/rendu/PSU_2014_philo
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 19:44:27 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 19:44:29 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "philo.h"

void		take_chopstick(t_philosopher *philo, t_chopstick *stick)
{
  if (philo->which == LEFT || philo->which == RIGHT)
    philo->which = BOTH;
  else if (stick->id == philo->id)
    philo->which = LEFT;
  else
    philo->which = RIGHT;
}

void		check_neighboors(t_philosopher *philo)
{
  int		move_addr;

  move_addr = (philo->id == 0 ? ((int)philo->data->nb_philo - 1) : -1);
  if ((philo + move_addr)->state == THINK)
    return;
  move_addr = (philo->id == philo->data->nb_philo - 1 ?
	       -(philo->data->nb_philo - 1) : 1);
  if ((philo + move_addr)->state == THINK)
    return;
  if (pthread_mutex_trylock(&(philo->tab[philo->id].handler)) == 0)
    take_chopstick(philo, &(philo->tab[philo->id]));
  if (pthread_mutex_trylock
      (&(philo->tab[(philo->id + 1) % philo->data->nb_philo].handler)) == 0)
    take_chopstick(philo,
		   &(philo->tab[(philo->id + 1) % philo->data->nb_philo]));
}

void		look_for_chopsticks(t_philosopher *philo)
{
  if (philo->which == NONE)
    check_neighboors(philo);
  else if (philo->which == LEFT || philo->which == RIGHT)
    {
      if (philo->which == RIGHT && pthread_mutex_trylock
	  (&(philo->tab[philo->id].handler)) == 0)
	take_chopstick(philo, &(philo->tab[philo->id]));
      else if (philo->which == LEFT && pthread_mutex_trylock
	       (&(philo->tab[(philo->id + 1) % philo->data->nb_philo].handler))
	       == 0)
	take_chopstick
	  (philo, &(philo->tab[(philo->id + 1) % philo->data->nb_philo]));
    }
  else
    {
      philo->which = NONE;
      pthread_mutex_unlock(&(philo->tab[philo->id].handler));
      pthread_mutex_unlock
	(&(philo->tab[(philo->id + 1) % philo->data->nb_philo].handler));
    }
}
