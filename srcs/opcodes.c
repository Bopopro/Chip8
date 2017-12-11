#include <stdio.h>
#include "opcodes.h"

const t_opcodes	g_opcodes[OPCODES_LENGTH] = {
  {0x0FFF, 0x0000, &op_0XXX},
  {0xFFFF, 0x00E0, &op_00E0},
  {0xFFFF, 0x00EE, &op_00EE},
  {0xF000, 0x1000, &op_1XXX},
  {0xF000, 0x2000, &op_2XXX},
  {0xF000, 0x3000, &op_3XXX},
  {0xF000, 0x4000, &op_4XXX},
  {0xF000, 0x5000, &op_5XXX},
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
  {0xF00F, 0x9000, &op_9XXX},
  {0xF000, 0xA000, &op_AXXX},
  {0xF000, 0xB000, &op_BXXX},
  {0xF000, 0xC000, &op_CXXX},
  {0xF000, 0xD000, &op_DXXX},
  {0xF0FF, 0xE09E, &op_EX9E},
  {0xF0FF, 0xE0A1, &op_EXA1},
  {0xF00F, 0xF007, &op_FXX7},
  {0xF00F, 0xF00A, &op_FXXA},
  {0xF0FF, 0xF015, &op_FX15},
  {0xF0FF, 0xF018, &op_FX18},
  {0xF0FF, 0xF01E, &op_FX1E},
  {0xF0FF, 0xF029, &op_FX29},
  {0xF0FF, 0xF033, &op_FX33},
  {0xF0FF, 0xF055, &op_FX55},
  {0xF0FF, 0xF065, &op_FX65}
};

int	op_0XXX(t_cpu *cpu){}
int	op_00E0(t_cpu *cpu){}
int	op_00EE(t_cpu *cpu){}

int	op_1XXX(t_cpu *cpu){
  cpu->pc = cpu->vars.nnn;
  printf("[DEBUG][1XXX]Jump: %d\n", cpu->pc);
}

int	op_2XXX(t_cpu *cpu){
  cpu->stack[cpu->sp] = cpu->pc;
  cpu->sp++;
  cpu->pc = cpu->vars.nnn;
  printf("[DEBUG][2XXX]Jump: %d Sp: %d TopStack: %d\n", cpu->pc, cpu->sp, cpu->stack[cpu->sp - 1]);
}

int	op_3XXX(t_cpu *cpu){
  if (cpu->reg[cpu->vars.x] == cpu->vars.kk) {
    cpu->pc++;
    printf("[DEBUG][3XXX]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
  }
}

int	op_4XXX(t_cpu *cpu){}
int	op_5XXX(t_cpu *cpu){}

int	op_6XXX(t_cpu *cpu){
  cpu->reg[cpu->vars.x] = cpu->vars.kk;
  printf("[DEBUG][6XXX]reg: %d val: %d\n", cpu->vars.x, cpu->vars.kk);
}

int	op_7XXX(t_cpu *cpu){
  cpu->reg[cpu->vars.x] += cpu->vars.kk;
  printf("[DEBUG][7XXX]reg: %d add: %d val: %d\n", cpu->vars.x, cpu->vars.kk, cpu->reg[cpu->vars.x]);
}

int	op_8XX0(t_cpu *cpu){}
int	op_8XX1(t_cpu *cpu){}
int	op_8XX2(t_cpu *cpu){}
int	op_8XX3(t_cpu *cpu){}
int	op_8XX4(t_cpu *cpu){}
int	op_8XX5(t_cpu *cpu){}
int	op_8XX6(t_cpu *cpu){}
int	op_8XX7(t_cpu *cpu){}
int	op_8XXE(t_cpu *cpu){}
int	op_9XXX(t_cpu *cpu){}

int	op_AXXX(t_cpu *cpu){
  cpu->I = cpu->vars.nnn;
  printf("[DEBUG][AXXX]reg: I val: %d\n", cpu->I);
}

int	op_BXXX(t_cpu *cpu){}
int	op_CXXX(t_cpu *cpu){}

int	op_DXXX(t_cpu *cpu){
  printf("[DEBUG][DXXX] Not Implemented\n");
}

int	op_EX9E(t_cpu *cpu){}
int	op_EXA1(t_cpu *cpu){}
int	op_FXX7(t_cpu *cpu){}
int	op_FXXA(t_cpu *cpu){}
int	op_FX15(t_cpu *cpu){}
int	op_FX18(t_cpu *cpu){}
int	op_FX1E(t_cpu *cpu){}
int	op_FX29(t_cpu *cpu){}
int	op_FX33(t_cpu *cpu){}
int	op_FX55(t_cpu *cpu){}
int	op_FX65(t_cpu *cpu){}
