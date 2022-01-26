#include <string.h>
#include <stdlib.h>
#include "register_machine.h"

unsigned long output_result(RegisterMachine *registerMachine, const unsigned long *inputRegisters,
                           int registerCount, unsigned int maxInstructionLimit) {

    unsigned int instructionsPerformed = 0;
    unsigned long registers[registerMachine->registerCount];

    if (registerCount > registerMachine->registerCount) {
        perror("Exceeded the number of input registers");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < registerCount; i++) {
        registers[i] = inputRegisters[i];
    }

    for (int i = registerCount; i < registerMachine->registerCount; i++) {
        registers[i] = 0;
    }

    unsigned int currentInstruction = 0;

    while (instructionsPerformed < maxInstructionLimit) {
        instructionsPerformed++;

        if (currentInstruction >= registerMachine->instructionCount) {
            perror("Instruction not found");
            exit(EXIT_FAILURE);
        }

        Instruction *instruction = registerMachine->instructions + currentInstruction;
        switch (instruction->type) {
            case HALT:
                return registers[0];
            case INCJ:
                registers[instruction->labels[0]]++;
                currentInstruction = instruction->labels[1];
                break;
            case DECC:
                if (registers[instruction->labels[0]] != 0) {
                    registers[instruction->labels[0]]--;
                    currentInstruction = instruction->labels[1];
                } else {
                    currentInstruction = instruction->labels[2];
                }
                break;
        }
    }
    perror("Exceeded maximum number of instructions performed");
    exit(EXIT_FAILURE);
}

RegisterMachine construct_register_machine(FILE *fp) {

    RegisterMachine registerMachine;
    registerMachine.instructions = malloc(sizeof(Instruction) * 8);

    if (registerMachine.instructions == NULL) {
        free(registerMachine.instructions);
        perror("Cannot allocate memory");
        exit(EXIT_FAILURE);
    }

    size_t bufferSize = 32;
    char buffer[bufferSize];
    char *bufferPointer = buffer;
    unsigned int instructionCount = 0;
    unsigned int instructionCountMax = 8;
    unsigned int registerCount = 0;

    while (getline(&bufferPointer, &bufferSize, fp) != -1) {

        if (instructionCount == instructionCountMax) {
            void *temp;
            if ((temp = realloc(registerMachine.instructions,
                                                        sizeof(Instruction) * (instructionCountMax *= 2))) == NULL) {
                free(registerMachine.instructions);
                perror("Cannot allocate memory");
                exit(EXIT_FAILURE);
            } else registerMachine.instructions = temp;
        }

        Instruction instruction;
        char *token;

        token = strtok(buffer, " ");
        if (strcmp(token, "HALT") == 0) {
            instruction.type = HALT;
        } else if (strcmp(token, "INCJ") == 0) {
            instruction.type = INCJ;
        } else if (strcmp(token, "DECC") == 0) {
            instruction.type = DECC;
        } else {
            perror("Unmatched instruction type");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < instruction.type; i++) {
            if ((instruction.labels[i] = strtoul(strtok(NULL, " "),
                                                 NULL, 10)) >= registerCount && i == 0) {
                registerCount = instruction.labels[i] + 1;
            }
        }
        registerMachine.instructions[instructionCount] = instruction;
        instructionCount++;
    }

    void *temp;
    if ((temp = realloc(registerMachine.instructions, sizeof(Instruction) * instructionCount)) == NULL) {
        free(registerMachine.instructions);
        perror("Cannot allocate memory");
        exit(EXIT_FAILURE);
    } else registerMachine.instructions = temp;

    registerMachine.registerCount = registerCount;
    registerMachine.instructionCount = instructionCount;

    return registerMachine;
}

void destruct_register_machine(RegisterMachine *registerMachine) {
    free(registerMachine->instructions);
}
