/*
** my_realloc.c for my_realloc in /home/girard_r/rendu/PSU_2014_malloc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Jan 29 11:56:46 2015 Aurélien GIRARDEAU
** Last update Fri Feb  6 18:16:10 2015 Aurélien GIRARDEAU
*/

#include <string.h>
#include "header.h"

static t_header	greater_size(t_header current, void *ptr, size_t new_size)
{
  t_header	new;

  pthread_mutex_unlock(&g_mutex);
  if ((new = malloc(new_size)) == NULL)
    return NULL;
  pthread_mutex_lock(&g_mutex);
  memcpy(new, ptr, MIN(current->size, get_four_sup(new_size)));
  pthread_mutex_unlock(&g_mutex);
  free(ptr);
  return (new);
}

static void	optimize_memory(t_header current, size_t new_size)
{
  fusion(current);
  if (current->size - new_size >= HEADER_SIZE)
    split_memory(current, new_size);
}

static void	lower_size(t_header current, size_t new_size)
{
  if (current->size - new_size >= HEADER_SIZE)
    split_memory(current, new_size);
}

void		*realloc(void *ptr, size_t size)
{
  size_t	new_size;
  t_header	current;

  pthread_mutex_lock(&g_mutex);
  new_size = get_four_sup(size);
  if (ptr == NULL)
    {
      pthread_mutex_unlock(&g_mutex);
      return (malloc(new_size));
    }
  current = get_block_addr(ptr);
  if (current->size >= new_size)
      lower_size(current, new_size);
  else
    {
      if (current->next && current->next->is_free == 1
	  && (current->size + current->next->size) >= new_size)
	  optimize_memory(current, new_size);
      else
	return (greater_size(current, ptr, new_size));
    }
  pthread_mutex_unlock(&g_mutex);
  return ptr;
}
