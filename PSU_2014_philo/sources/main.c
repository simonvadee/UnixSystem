/*
** main.c for philo in /home/girard_r/rendu/PSU_2014_philo
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 19:43:50 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 19:48:54 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

char		get_graph(int set)
{
  static char	graph = 0;

  if (set == 1)
    graph = 1;
  return graph;
}

int		main()
{
  t_chopstick	*sticks;
  t_philosopher	*philo;
  unsigned int	cmp;

  cmp = 0;
  philo = NULL;
  if (parse_entry(&sticks, &philo))
    return (-1);
  while (cmp != philo->data->nb_philo)
    {
      pthread_join(philo[cmp].instance, NULL);
      cmp++;
    }
  if (get_graph(0) == 1)
    process_events();
  free(sticks);
  free(philo->data);
  free(philo);
  return 0;
}
