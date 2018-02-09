#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "window.h"
#include "opcodes.h"
#include "chip8.h"

extern const t_opcodes	g_opcodes[OPCODES_LENGTH];

static void	c8_init_font(t_cpu *cpu) {
  uint8_t font[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };

  for (uint16_t i = 0; i < 0x50; i++)
    cpu->mem[i] = font[i];
}

void	c8_dump_memory(t_cpu *cpu) {
  printf("[DUMP][PC] %d\n", cpu->pc);
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

  cpu = calloc(sizeof(t_cpu), 1);
  if (!cpu)
    return (NULL);
  cpu->pc = PRG_START;
  c8_init_font(cpu);
  if (c8_read_program(cpu, filepath) == C8_FAILURE)
    return (NULL);
  return (cpu);
}

t_variable	*c8_actualise_var(t_variable *var, uint16_t opcode) {
  var->nnn = opcode & 0x0FFF;
  var->n = opcode & 0x000F;
  var->x = (opcode & 0x0F00) >> 8;
  var->y = (opcode & 0x00F0) >> 4;
  var->kk = opcode & 0x00FF;
  return (var);
}

void	c8_start(t_cpu *cpu, t_window *win) {
  uint16_t	c_opcode = 0x0;
  sfClock	*c8_clock;

  c8_clock = sfClock_create();
  while (sfRenderWindow_isOpen(win->window)) {
    c_opcode = (cpu->mem[cpu->pc] << 8) | cpu->mem[cpu->pc + 1];
    cpu->pc += 2;
    for (uint8_t j = 0; j < OPCODES_LENGTH; j++) {
      if ((c_opcode & g_opcodes[j].mask) == g_opcodes[j].code) {
        c8_actualise_var(&cpu->vars, c_opcode);
        g_opcodes[j].op(cpu, win);
        break;
      }
    }
    if (cpu->delay > 0 && sfClock_getElapsedTime(c8_clock).microseconds >= 16) {
      cpu->delay--;
      sfClock_restart(c8_clock);
    }
    if (cpu->delay > 0)
      cpu->delay--;
    sfTexture_updateFromPixels(win->texture, win->fb->pixels, WIDTH, HEIGHT, 0, 0);
    while (sfRenderWindow_pollEvent(win->window, &win->event)) {
      if (win->event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(win->window);
    }
    sfRenderWindow_clear(win->window, sfBlack);
    sfRenderWindow_drawSprite(win->window, win->sprite, NULL);
    sfRenderWindow_display(win->window);
  }
}
