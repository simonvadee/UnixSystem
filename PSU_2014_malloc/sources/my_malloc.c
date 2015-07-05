/*
** my_malloc.c for my_malloc in /home/girard_r/rendu/PSU_2014_malloc/sources
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Tue Jan 27 16:41:46 2015 Aurélien GIRARDEAU
** Last update Fri Feb  6 18:15:09 2015 Aurélien GIRARDEAU
*/

#include "header.h"

t_header		g_base = NULL;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void		*first_malloc(size_t size)
{
  g_base = increment_heap(size, NULL);
  if (!g_base)
    return (NULL);
  return ((void *)((char *)g_base + HEADER_SIZE));
}

void			split_memory(t_header toSplit, size_t size)
{
  t_header		new_mem;

  new_mem = (t_header)((char *)toSplit + HEADER_SIZE + size);
  new_mem->size = toSplit->size - size - HEADER_SIZE;
  new_mem->is_free = 1;
  toSplit->size = size;
  new_mem->prev = toSplit;
  new_mem->next = toSplit->next;
  toSplit->next = new_mem;
  toSplit->is_free = 0;
  if (new_mem->next)
    new_mem->next->prev = new_mem;
}

static void		*seek_malloc(size_t size)
{
  t_header		tmp;
  t_header		last;

  if (!(tmp = find_chunk(size, &last)))
    tmp = increment_heap(size, last);
  else
    if (((int)tmp->size - (int)size - HEADER_SIZE) >= 0)
      split_memory(tmp, size);
  return ((void*)((char *)tmp + HEADER_SIZE));
}

void			*malloc(size_t size)
{
  size_t		new_size;
  void			*ret;

  pthread_mutex_lock(&g_mutex);
  new_size = get_four_sup(size);
  if (!g_base)
    ret = first_malloc(new_size);
  else
    ret = seek_malloc(new_size);
  pthread_mutex_unlock(&g_mutex);
  return (ret);
}
