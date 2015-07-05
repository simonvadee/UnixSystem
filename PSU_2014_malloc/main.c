#include "includes/header.h"

int main()
{
  char *test;
  char *titi;

  test = malloc(4522);
  show_alloc_mem();
  titi = malloc(1);
  show_alloc_mem();
  return 0;
}
