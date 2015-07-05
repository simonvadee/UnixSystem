/*
** my_free.c for malloc in /home/girard_r/rendu/PSU_2014_malloc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Jan 29 11:31:34 2015 Aurélien GIRARDEAU
** Last update Fri Feb  6 15:36:16 2015 Aurélien GIRARDEAU
*/

#include "header.h"

t_header	get_block_addr(void *ptr)
{
  ptr = ((char*)ptr - HEADER_SIZE);
  return (ptr);
}

int		valid(void *ptr)
{
  if (g_base && ptr)
    {
      if (ptr >= (void *)g_base && ptr < sbrk(0))
	return (ptr == (void *)((char *)get_block_addr(ptr) + HEADER_SIZE));
    }
  return (0);
}

void       	fusion(t_header ptr)
{
  ptr->size += HEADER_SIZE + ptr->next->size;
  ptr->next = ptr->next->next;
  if (ptr->next)
    ptr->next->prev = ptr;
}

void		free(void *ptr)
{
  t_header	tmp;
  int		pagesize;

  pthread_mutex_lock(&g_mutex);
  if (!valid(ptr))
    {
      pthread_mutex_unlock(&g_mutex);
      return ;
    }
  tmp = get_block_addr(ptr);
  tmp->is_free = 1;
  while (tmp->next && tmp->next->is_free == 1)
    fusion(tmp);
  pagesize = getpagesize();
  if ((int)(tmp->size + HEADER_SIZE) == pagesize && !tmp->next)
    {
      if (tmp->prev)
	tmp->prev->next = NULL;
      else
	g_base = NULL;
      sbrk(-pagesize);
    }
  pthread_mutex_unlock(&g_mutex);
}
