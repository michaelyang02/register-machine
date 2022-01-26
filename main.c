#include <stdio.h>
#include <stdlib.h>
#include "register_machine.h"

int main(int argc, char *argv[]) {

    // Usage: regmac <register machine file> <initial register values>

    if (argc < 3) {
        perror("Too few arguments");
        exit(EXIT_FAILURE);
    }

    FILE *fp;

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    RegisterMachine registerMachine = construct_register_machine(fp);

    unsigned long inputRegisters[argc - 2];
    for (int i = 2; i < argc; i++) {
        inputRegisters[i - 2] = strtol(argv[i], NULL, 10);
    }

    printf("%lu", output_result(&registerMachine,
                                inputRegisters, argc - 2, 100000000));

    destruct_register_machine(&registerMachine);

    return 0;
}
