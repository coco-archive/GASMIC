#include <as.h>
#include <arch.h>

/*
 * struc?
 * .org
 * .equ
 * .include
 * .org
 * .resb
 * .fcb
 * .extern
 * .global
 * .ascii
 * .asciz
 * .extern
 * .global
 */

static void pseudo_arch(Line *line);
static void pseudo_equ(Line *line);
static void pseudo_include(Line *line);
static void pseudo_org(Line *line);

static struct pseudo_instruction pseudo_ops[] = {
    { ".ARCH", &pseudo_arch, 1 },
    { ".EQU", &pseudo_equ, 1 },
    { ".INCLUDE", &pseudo_include, 1 },
    { ".ORG", &pseudo_org, 1 },
    { "", NULL, 0 }
};

struct pseudo_instruction *get_pseudo_op(Line *line) {
    struct pseudo_instruction *pseudo_op;
    for (pseudo_op = pseudo_ops; *pseudo_op->instruction != '\0'; pseudo_op++) {
        if (streq(line->mnemonic, (*line->mnemonic == '.' ? pseudo_op->instruction : &pseudo_op->instruction[1]))) {
            return pseudo_op;
        }
    }
    return NULL;
}

void parse_pseudo_op(Line *line) {
    /*struct pseudo_instruction *pseudo_inst;
    for (pseudo_inst = pseudo_ops; pseudo_inst->instruction[0] != '\0'; pseudo_inst++) {
        if (streq(line->mnemonic, pseudo_inst->instruction)) {
            pseudo_inst->process(line);
            return;
        }
    }*/
    struct pseudo_instruction *pseudo_inst = get_pseudo_op(line);
    if (pseudo_inst == NULL) {
        die("Error on line %ld: unable to find pseudo instruction %s\n", line_num, line->mnemonic);
    }
    pseudo_inst->process(line);
}

static void pseudo_arch(Line *line) {    
    if (datatab->first == NULL) {
        Architecture *arch = str_to_arch(line->argv[0].val.str);
        if (arch == NULL) {
            die("Failed to locate architecture %s\n", line->argv[0].val.str);
        }
        configuration.arch = arch;
        printf("%s\n", configuration.arch->name);
    }
    else {
        die("Cannot switch architecture after code\n")
    }
}

static void pseudo_equ(Line *line) {
    if (!(line->line_state & LABEL_STATE)) {
        die("Error on line %ld. Pseudo instruction .EQU requires a label on the same line\n", line_num);
    }
    if (line->argc != 1) {
        die("Error on line %ld. Invalid number of arguments for pseudo instruction .EQU\n", line_num);
    }
    
    char *num_end;
    symtab->last->value = strtol(line->argv[0].val.str, &num_end, 0);
    //if (line->argv[0] == num_end) {
    if (*num_end != '\0') {
        die("Error on line %ld. Failed to parse given value\n", line_num);
    }
}

static void pseudo_include(Line *line) {
    FILE *included_file;
    if ((included_file = fopen(line->argv[0].val.str, "r")) == NULL) {
        die("Failed to open included file \"%s\" on line %ld\n", line->argv[0].val.str, line_num);
    }
    
    //Line *new_line = salloc(sizeof(Line));
    assemble(included_file, line);
    fclose(included_file);
    //sfree(new_line);
    
    // need to reassign argv because assemble frees it but we return back to assemble.
    line->argc = 1;
    line->argv = salloc(line->argc * sizeof(char *));
}

static void pseudo_org(Line *line) {
    char *lend;
    address = strtol(line->argv[0].val.str, &lend, 0);
    if (lend == line->argv[0].val.str || *lend != '\0') {
        die("value is not a number on line %ld\n", line_num);
    }
}
