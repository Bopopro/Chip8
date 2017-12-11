#pragma once

# include <stdlib.h>
# include "chip8.h"

# define OPCODES_LENGTH	(35)


typedef struct	s_opcodes {
  uint16_t	mask;
  uint16_t	code;
  int		(*op)(t_cpu*);
}		t_opcodes;

int	op_0XXX(t_cpu*);
int	op_00E0(t_cpu*);
int	op_00EE(t_cpu*);
int	op_1XXX(t_cpu*);
int	op_2XXX(t_cpu*);
int	op_3XXX(t_cpu*);
int	op_4XXX(t_cpu*);
int	op_5XX0(t_cpu*);
int	op_6XXX(t_cpu*);
int	op_7XXX(t_cpu*);
int	op_8XX0(t_cpu*);
int	op_8XX1(t_cpu*);
int	op_8XX2(t_cpu*);
int	op_8XX3(t_cpu*);
int	op_8XX4(t_cpu*);
int	op_8XX5(t_cpu*);
int	op_8XX6(t_cpu*);
int	op_8XX7(t_cpu*);
int	op_8XXE(t_cpu*);
int	op_9XX0(t_cpu*);
int	op_AXXX(t_cpu*);
int	op_BXXX(t_cpu*);
int	op_CXXX(t_cpu*);
int	op_DXXX(t_cpu*);
int	op_EX9E(t_cpu*);
int	op_EXA1(t_cpu*);
int	op_FX07(t_cpu*);
int	op_FX0A(t_cpu*);
int	op_FX15(t_cpu*);
int	op_FX18(t_cpu*);
int	op_FX1E(t_cpu*);
int	op_FX29(t_cpu*);
int	op_FX33(t_cpu*);
int	op_FX55(t_cpu*);
int	op_FX65(t_cpu*);
