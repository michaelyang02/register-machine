#ifndef REGISTER_MACHINE_REGISTER_MACHINE_H
#define REGISTER_MACHINE_REGISTER_MACHINE_H

#include <stdbool.h>
#include <stdio.h>

typedef enum InstructionForm_t {
    HALT = 0,  // halt
    INCJ = 2, // increment jump
    DECC = 3, // decrement condition
} InstructionForm;

typedef struct Instruction_t {
    InstructionForm type;
    unsigned int labels[3];
} Instruction;

typedef struct RegisterMachine_t {
    Instruction *instructions;
    unsigned int instructionCount;
    unsigned int registerCount;
} RegisterMachine;

unsigned long output_result(RegisterMachine *registerMachine, const unsigned long *inputRegisters,
                           int registerCount, unsigned int maxInstructionLimit);

RegisterMachine construct_register_machine(FILE *fp);

void destruct_register_machine(RegisterMachine *registerMachine);

#endif //REGISTER_MACHINE_REGISTER_MACHINE_H
