#include <stdlib.h>
#include "window.h"
#include "chip8.h"

int main(int ac, char **av)
{
  t_cpu		*cpu;
  t_window	*win;

  (void)ac;
  win = c8_init_window();
  cpu = c8_init_chip8(av[1]);
  if (!win || !cpu)
    return (C8_FAILURE);
  //c8_dump_memory(cpu);
  c8_start(cpu, win);
  free(cpu);
  return 0;
}
