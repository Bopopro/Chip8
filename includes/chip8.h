#pragma once

#include <stdint.h>

# define RAM			(4096)
# define PRG_START		(0x200)
# define REGISTER_LENGTH	(0x10)
# define STACK_LENGTH		(0x10)

# define C8_FAILURE		(-1)
# define C8_SUCCESS		(0)

typedef struct	s_cpu {
  uint8_t	mem[RAM];
  uint8_t	reg[REGISTER_LENGTH];
  uint16_t	I;
  uint8_t	soundTimer;
  uint8_t	delay;
  uint16_t	pc;
  uint8_t	sp;
  uint16_t	stack[STACK_LENGTH];
}		t_cpu;

typedef struct	s_variable {
  uint16_t	nnn;
  uint8_t	n;
  uint8_t	x;
  uint8_t	y;
  uint8_t	kk;
}		t_variable;

t_cpu		*c8_init_chip8();
void		c8_dump_memory(t_cpu *cpu);
t_variable	*c8_actualise_var(t_variable *var, uint16_t opcode);
void		c8_start(t_cpu *cpu);
