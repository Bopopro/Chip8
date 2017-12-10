#include <stdlib.h>
#include "chip8.h"

int main(int ac, char **av)
{
  t_cpu	*cpu;

  (void)ac;
  cpu = c8_init_chip8(av[1]);
  //c8_dump_memory(cpu);
  c8_start(cpu);
  free(cpu);
  return 0;
}
