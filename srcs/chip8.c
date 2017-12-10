#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

static void	c8_init_font(t_cpu *cpu) {
  uint8_t font[] = {
    //0    
    0b01100000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b01100000,
    //1    
    0b01100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01110000,
    //2    
    0b11110000,
    0b10010000,
    0b11110000,
    0b10000000,
    0b11110000,
    //3    
    0b11110000,
    0b00010000,
    0b11110000,
    0b00010000,
    0b11110000,
    //4    
    0b10010000,
    0b10010000,
    0b11110000,
    0b10010000,
    0b00010000,
    //5    
    0b11110000,
    0b10000000,
    0b11110000,
    0b00010000,
    0b11110000,
    //6    
    0b11110000,
    0b10000000,
    0b11110000,
    0b10010000,
    0b11110000,
    //7    
    0b11110000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b01000000,
    //8    
    0b11110000,
    0b10010000,
    0b11110000,
    0b10010000,
    0b11110000,
    //9    
    0b11110000,
    0b10010000,
    0b11110000,
    0b00010000,
    0b01110000,
    //A    
    0b11110000,
    0b10010000,
    0b11110000,
    0b10010000,
    0b10010000,
    //B    
    0b11100000,
    0b10010000,
    0b11100000,
    0b10010000,
    0b11100000,
    //C    
    0b11110000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b11110000,
    //D
    0b11100000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b11100000,
    //E    
    0b11110000,
    0b10000000,
    0b11110000,
    0b10000000,
    0b11110000,
    //F    
    0b11110000,
    0b10000000,
    0b11110000,
    0b10000000,
    0b10000000,
  };

  for (uint16_t i = 0; i < 0x50; i++)
    cpu->mem[i] = font[i];
}

void	c8_dump_memory(t_cpu *cpu) {
  for (uint16_t i = 0; i < RAM; i++) {
    if (i == cpu->pc)
      printf("\e[31m%2x\e[0m ", cpu->mem[i]);
    else
      printf("%02x ", cpu->mem[i]);
    if (i % 32 == 0)
      putchar('\n');
  }
}

static int	c8_read_program(t_cpu *cpu, const char * const filepath) {
  FILE		*file;

  file = fopen(filepath, "r");
  if (!file)
    return (C8_FAILURE);
  fread(cpu->mem + PRG_START, sizeof(uint8_t), RAM - PRG_START, file);
  if (ferror(file) != 0)
    return (C8_FAILURE);
  fclose(file);
  return (C8_SUCCESS);
}

t_cpu *c8_init_chip8(const char * const filepath) {
  t_cpu *cpu;
  printf("HELLO\n");

  cpu = calloc(sizeof(t_cpu), 1);
  if (!cpu)
    return (NULL);
  cpu->pc = PRG_START;
  c8_init_font(cpu);
  if (c8_read_program(cpu, filepath) == C8_FAILURE)
    return (NULL);
  return (cpu);
}
