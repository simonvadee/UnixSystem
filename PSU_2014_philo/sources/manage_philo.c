/*
** manage_philo.c for philo in /home/girard_r/rendu/PSU_2014_philo
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 19:44:06 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 19:52:48 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "philo.h"

void		eat(t_philosopher *philo, char display)
{
  philo->state = EAT;
  philo->rice -= 1;
  (void)display;
  if (display)
    change_state(philo->id, EAT);
  printf("philosopher %d eating... %d rice remaining\n",
	 philo->id, philo->rice);
  sleep(philo->data->time_eating);
}

void		think(t_philosopher *philo, char display)
{
  philo->state = THINK;
  (void)display;
  if (display)
    change_state(philo->id, THINK);
  printf("philosopher %d thinking... %d rice remaining\n",
	 philo->id, philo->rice);
  sleep(philo->data->time_thinking);
}

void		rest(t_philosopher *philo, char display)
{
  philo->state = REST;
  (void)display;
  if (display)
    change_state(philo->id, REST);
  printf("philosopher %d resting... %d rice remaining\n",
	 philo->id, philo->rice);
  sleep(1);
}

void		*philo_routine(void *arg)
{
  t_philosopher	*philo;
  char		display;

  philo = (t_philosopher*)arg;
  display = philo->data->nb_philo == 7 ? 1 : 0;
  if (display)
    get_graph(1);
  while (philo->rice > 0)
    {
      look_for_chopsticks(philo);
      if (philo->which == BOTH)
	eat(philo, display);
      else if (philo->which == LEFT || philo->which == RIGHT)
	think(philo, display);
      else
	rest(philo, display);
    }
  look_for_chopsticks(philo);
  if (display)
    change_state(philo->id, REST);
  printf("philosoher %d has finished his food\n", philo->id);
  pthread_exit(NULL);
}
