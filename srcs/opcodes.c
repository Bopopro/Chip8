#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "opcodes.h"

static const sfKeyCode g_keyboard[] = {
  sfKeyX,
  sfKeyNum1,
  sfKeyNum2,
  sfKeyNum3,
  sfKeyA,
  sfKeyZ,
  sfKeyE,
  sfKeyQ,
  sfKeyS,
  sfKeyD,
  sfKeyW,
  sfKeyC,
  sfKeyNum4,
  sfKeyR,
  sfKeyF,
  sfKeyV,
};

const t_opcodes	g_opcodes[OPCODES_LENGTH] = {
  {0x0000, 0x0FFF, &op_0XXX},
  {0xFFFF, 0x00E0, &op_00E0},
  {0xFFFF, 0x00EE, &op_00EE},
  {0xF000, 0x1000, &op_1XXX},
  {0xF000, 0x2000, &op_2XXX},
  {0xF000, 0x3000, &op_3XXX},
  {0xF000, 0x4000, &op_4XXX},
  {0xF000, 0x5000, &op_5XX0},
  {0xF000, 0x6000, &op_6XXX},
  {0xF000, 0x7000, &op_7XXX},
  {0xF00F, 0x8000, &op_8XX0},
  {0xF00F, 0x8001, &op_8XX1},
  {0xF00F, 0x8002, &op_8XX2},
  {0xF00F, 0x8003, &op_8XX3},
  {0xF00F, 0x8004, &op_8XX4},
  {0xF00F, 0x8005, &op_8XX5},
  {0xF00F, 0x8006, &op_8XX6},
  {0xF00F, 0x8007, &op_8XX7},
  {0xF00F, 0x800E, &op_8XXE},
  {0xF00F, 0x9000, &op_9XX0},
  {0xF000, 0xA000, &op_AXXX},
  {0xF000, 0xB000, &op_BXXX},
  {0xF000, 0xC000, &op_CXXX},
  {0xF000, 0xD000, &op_DXXX},
  {0xF0FF, 0xE09E, &op_EX9E},
  {0xF0FF, 0xE0A1, &op_EXA1},
  {0xF00F, 0xF007, &op_FX07},
  {0xF00F, 0xF00A, &op_FX0A},
  {0xF0FF, 0xF015, &op_FX15},
  {0xF0FF, 0xF018, &op_FX18},
  {0xF0FF, 0xF01E, &op_FX1E},
  {0xF0FF, 0xF029, &op_FX29},
  {0xF0FF, 0xF033, &op_FX33},
  {0xF0FF, 0xF055, &op_FX55},
  {0xF0FF, 0xF065, &op_FX65}
};

int	op_0XXX(t_cpu *cpu, t_window *win){
  printf("[DEBUG][0XXX] Not Implemented\n");
  return (0);
}
int	op_00E0(t_cpu *cpu, t_window *win){
  (void)cpu;
  c8_clear_framebuffer(win->fb);
  return (0);
}

int	op_00EE(t_cpu *cpu, t_window *win){
  (void)win;
  if (cpu->sp > 0) {
    cpu->pc = cpu->stack[cpu->sp - 1];
    cpu->sp--;
    printf("[DEBUG][00EE]Jump: %d Sp: %d\n", cpu->pc, cpu->sp);
  }
  return (0);
}

int	op_1XXX(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->pc = cpu->vars.nnn;
  printf("[DEBUG][1XXX]Jump: %d\n", cpu->pc);
  return (0);
}

int	op_2XXX(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->stack[cpu->sp] = cpu->pc;
  cpu->sp++;
  cpu->pc = cpu->vars.nnn;
  printf("[DEBUG][2XXX]Jump: %d Sp: %d TopStack: %d\n", cpu->pc, cpu->sp, cpu->stack[cpu->sp - 1]);
  return (0);
}

int	op_3XXX(t_cpu *cpu, t_window *win){
  (void)win;
  if (cpu->reg[cpu->vars.x] == cpu->vars.kk) {
    cpu->pc += sizeof(uint16_t);
    printf("[DEBUG][3XXX]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
  }
  return (0);
}

int	op_4XXX(t_cpu *cpu, t_window *win){
  (void)win;
 if (cpu->reg[cpu->vars.x] != cpu->vars.kk)
   cpu->pc += sizeof(uint16_t);
 printf("[DEBUG][4XXX]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
  return (0);
}
int	op_5XX0(t_cpu *cpu, t_window *win){
  (void)win;
  if (cpu->reg[cpu->vars.x] == cpu->reg[cpu->vars.y]) {
    cpu->pc += sizeof(uint16_t);
    printf("[DEBUG][5XXX]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
  }
  return (0);
}

int	op_6XXX(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] = cpu->vars.kk;
  printf("[DEBUG][6XXX]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
  return (0);
}

int	op_7XXX(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] += cpu->vars.kk;
  printf("[DEBUG][7XXX]reg: %d add: %d val: %d\n", cpu->vars.x, cpu->vars.kk, cpu->reg[cpu->vars.x]);
  return (0);
}

int	op_8XX0(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] = cpu->reg[cpu->vars.y];
  printf("[DEBUG][8XX0]Reg: %d Val: %d\n", cpu->vars.x, cpu->reg[cpu->vars.y]);
  return (0);
}
int	op_8XX1(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] |= cpu->reg[cpu->vars.y];
  printf("[DEBUG][8XX1]Reg: %d Val: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_8XX2(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] &= cpu->reg[cpu->vars.y];
  printf("[DEBUG][8XX2]Reg: %d Val: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_8XX3(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] ^= cpu->reg[cpu->vars.y];
  printf("[DEBUG][8XX3]Reg: %d Val: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_8XX4(t_cpu *cpu, t_window *win){
  uint16_t res;

  (void)win;
  res = cpu->reg[cpu->vars.x] + cpu->reg[cpu->vars.y];
  cpu->reg[0xF] = (res > 0xFF) ? (1) : (0);
  cpu->reg[cpu->vars.x] = res & 0xFF;
  printf("[DEBUG][8XX4]Reg: %d Val: %d F: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x], cpu->reg[0xF]);
  return (0);
}
int	op_8XX5(t_cpu *cpu, t_window *win){
  cpu->reg[0xF] = (cpu->reg[cpu->vars.x] > cpu->reg[cpu->vars.y]) ? (1) : (0);
  (void)win;
  cpu->reg[cpu->vars.x] -= cpu->reg[cpu->vars.y];
  printf("[DEBUG][8XX5]Reg: %d Val: %d F: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x], cpu->reg[0xF]);
  return (0);
}
int	op_8XX6(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[0xF] = (cpu->reg[cpu->vars.x] & 1) ? (1) : (0);
  cpu->reg[cpu->vars.x] /= 2;
  printf("[DEBUG][8XX6]Reg: %d Val: %d F: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x], cpu->reg[0xF]);
  return (0);
}
int	op_8XX7(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[0xF] = (cpu->reg[cpu->vars.y] > cpu->reg[cpu->vars.x]) ? (1) : (0);
  cpu->reg[cpu->vars.x] = cpu->reg[cpu->vars.y] - cpu->reg[cpu->vars.x];
  printf("[DEBUG][8XX7]Reg: %d Val: %d F: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x], cpu->reg[0xF]);
  return (0);
}
int	op_8XXE(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[0xF] = ((cpu->reg[cpu->vars.x] >> 7) & 1) ? (1) : (0);
  cpu->reg[cpu->vars.x] *= 2;
  printf("[DEBUG][8XXE]Reg: %d Val: %d F: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x], cpu->reg[0xF]);
  return (0);
}
int	op_9XX0(t_cpu *cpu, t_window *win){
  (void)win;
  if (cpu->reg[cpu->vars.x] != cpu->reg[cpu->vars.y]) {
    cpu->pc += sizeof(uint16_t);
    printf("[DEBUG][9XX0]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
  }
  return (0);
}

int	op_AXXX(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->I = cpu->vars.nnn;
  printf("[DEBUG][AXXX]reg: I val: %d\n", cpu->I);
  return (0);
}

int	op_BXXX(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->pc = cpu->vars.nnn + cpu->reg[0x0];
  printf("[DEBUG][BXXX]Jump: %d (%d + %d)\n", cpu->pc, cpu->vars.nnn, cpu->reg[0x0]);
  return (0);
}
int	op_CXXX(t_cpu *cpu, t_window *win){
  uint8_t r = 0;

  (void)win;
  srand(time(NULL));
  r = rand() % 0x100;
  cpu->reg[cpu->vars.x] = r & cpu->vars.kk;
  printf("[DEBUG][CXXX]Rand: %d Reg: %d Val: %d\n", r, cpu->vars.x, cpu->reg[cpu->vars.x]);
  return (0);
}

int	op_DXXX(t_cpu *cpu, t_window *win){
  uint8_t	x = cpu->reg[cpu->vars.x];
  uint8_t	y = cpu->reg[cpu->vars.y];

  for (size_t i = 0; i < cpu->vars.n; i++) {
    for (size_t j = 0; j < 8; j++) {
      uint8_t	n = cpu->mem[cpu->I + i];

      if ((n >> (7 - j)) & 1) {
        if (c8_is_pixel_set(win->fb, x + j, y + i))
          cpu->reg[0xF] = true;
        c8_toggle_pixel(win->fb, x + j, y + i);
      }
    }
  }
  printf("[DEBUG][DXXX]n: %d X: %d Y: %d\n", cpu->vars.n, cpu->reg[cpu->vars.x], cpu->reg[cpu->vars.y]);
  return (0);
}

int	op_EX9E(t_cpu *cpu, t_window *win){
  (void)win;

  if (sfKeyboard_isKeyPressed(g_keyboard[cpu->reg[cpu->vars.x]])) {
    printf("[DEBUG][EX9E][1] Pressed \n");
    cpu->pc += 2;
  }
  printf("[DEBUG][EX9E] Val: %d \n", cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_EXA1(t_cpu *cpu, t_window *win){
  (void)win;
  if (!sfKeyboard_isKeyPressed(g_keyboard[cpu->reg[cpu->vars.x]])) {
    printf("[DEBUG][EX9E][1] Pressed \n");
    cpu->pc += 2;
  }
  printf("[DEBUG][EX9E] Val: %d \n", cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_FX07(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->reg[cpu->vars.x] = cpu->delay;
  printf("[DEBUG][FXX7]Reg: %d Val: %d\n", cpu->vars.x, cpu->delay);
  return (0);
}
int	op_FX0A(t_cpu *cpu, t_window *win){
  (void)win;
  while (sfRenderWindow_pollEvent(win->window, &win->event)) {
    for (size_t i = 0; i < sizeof(g_keyboard) / sizeof(sfKeyCode); i++) {
      if (sfKeyboard_isKeyPressed(g_keyboard[i])) {
        cpu->reg[cpu->vars.x] = i;
        break;
      }
    }
  }
  printf("[DEBUG][FX0A]Key: %d\n", cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_FX15(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->delay = cpu->reg[cpu->vars.x];
  printf("[DEBUG][FX15]DelayTimer: %d\n", cpu->delay);
  return (0);
}
int	op_FX18(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->soundTimer = cpu->reg[cpu->vars.x];
  printf("[DEBUG][FX15]SoundTimer: %d\n", cpu->soundTimer);
  return (0);
}
int	op_FX1E(t_cpu *cpu, t_window *win){
  (void)win;
  cpu->I += cpu->reg[cpu->vars.x];
  printf("[DEBUG][FX1E] I: %d\n", cpu->I);
  return (0);
}
int	op_FX29(t_cpu *cpu, t_window *win){
  (void)win;

  cpu->I = cpu->reg[cpu->vars.x] * 5;
  printf("[DEBUG][FX29]I: %d Sprite: %d\n", cpu->I, cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_FX33(t_cpu *cpu, t_window *win){
  uint8_t x;

  (void)win;
  x = cpu->reg[cpu->vars.x];
  cpu->mem[cpu->I] = x % 10;
  cpu->mem[cpu->I + 1] = (x / 10) % 10;
  cpu->mem[cpu->I + 2] = (x / 100) % 10;
  printf("[DEBUG][FX33]Reg: %d Val: %d\n", cpu->vars.x, cpu->reg[cpu->vars.x]);
  return (0);
}
int	op_FX55(t_cpu *cpu, t_window *win){
  (void)win;
  for (uint8_t i = 0; i <= cpu->vars.x; i++)
    cpu->mem[cpu->I + i] = cpu->reg[i];
  printf("[DEBUG][FX55]I: %d X: %d\n", cpu->I, cpu->vars.x);
  cpu->I += cpu->vars.x + 1;
  return (0);
}
int	op_FX65(t_cpu *cpu, t_window *win){
  (void)win;
  for (uint8_t i = 0; i <= cpu->vars.x; i++)
    cpu->reg[i] = cpu->mem[cpu->I + i];
  printf("[DEBUG][FX65]I: %d X: %d\n", cpu->I, cpu->vars.x);
  cpu->I += cpu->vars.x + 1;
  return (0);
}
