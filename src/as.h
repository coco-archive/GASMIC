#ifndef _AS_H
#define _AS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <smem.h>

#define DEBUG

#define streq(__s1, __s2) !strcmp((const char *)__s1, (const char *)__s2)

#define MAXMNEMONICSIZE 10
typedef struct {
    char mne[MAXMNEMONICSIZE];
    int arcs;
    int regs;
    int addr_modes;
    uint16_t base_opcode;
    int op_shift;
} Instruction;


#define LABEL_STATE (1)
#define MNEMONIC_STATE (2)
#define QUOTE_STATE (4)
typedef struct {
    char *label;
    char *mnemonic;
    char **argv;
    size_t argc;
    unsigned char arg_buf_size;
    unsigned char line_state;
} Line;

typedef struct symtab_entry {
    char *label;
    size_t value;
    struct symtab_entry *next;
} Symbol;

typedef struct {
    Symbol *first;
    Symbol *last;
} SymTab;

extern size_t line_num;
extern SymTab *symtab;

void assemble(FILE *in, Line *l);
void parse_pseudo_op(Line *line);

#endif
