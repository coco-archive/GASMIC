#ifndef MC6x09_ARCH_H
#define MC6x09_ARCH_H

#include <as.h>

//#define ENDIANNESS ARCH_BIG_ENDIAN

//#define DEFAULT_SYNTAX SYNTAX_MOTOROLA

#define MC6809 (1)
#define HD6309 (2)

#define MC6809_REG_INVALID (-1)
#define MC6809_REG_NONE    (0)
#define MC6809_REG_A       (1)
#define MC6809_REG_B       (2)
#define MC6809_REG_D       (3)
#define MC6809_REG_X       (4)
#define MC6809_REG_Y       (5)
#define MC6809_REG_U       (6)
#define MC6809_REG_S       (7)
#define MC6809_REG_PC      (8)
#define MC6809_REG_DP      (9)
#define MC6809_REG_CC      (10)
#define HD6309_REG_E       (11)
#define HD6309_REG_F       (12)
#define HD6309_REG_W       (13)
#define HD6309_REG_Q       (14)
#define HD6309_REG_V       (15)
#define HD6309_REG_Z       (16)
#define HD6309_REG_MD      (17)

#define MC6809_ADDR_MODE_INVALID    (0)
#define MC6809_ADDR_MODE_INH        (1)
#define MC6809_ADDR_MODE_IMM        (2)
#define MC6809_ADDR_MODE_DIR        (3)
#define MC6809_ADDR_MODE_IND        (4)
#define MC6809_ADDR_MODE_EXT        (5)
#define MC6809_ADDR_MODE_INTER      (6)

typedef ARCH_INSTRUCTION(MC6809, uint16_t, 17, 6) MC6x09_Instruction;

//typedef uint16_t addr_t;

extern size_t address;
//extern Architecture architectures[];
//extern Register registers[];
//extern Instruction instructions[];

extern Architecture *ARCH_MC6809;
extern Architecture *ARCH_HD6309;

void MC6809_init(void);
void HD6309_init(void);

#endif
