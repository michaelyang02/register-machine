# register-machine

This is an implementation of a register machine written in C. A register machine has a finite list of labelled instructions as well as a finite number of registers, and it is able to process some initial register value inputs, and in a deterministic fashion, either halt and output a value in one of its registers or never halt. Here, we assume the register machine is able to take a few elementary instructions:
  - `INCJ Rn Lx`: increment the content of the register numbered `n` and jump to the instruction labelled `x`.
  - `DECC Rn Lx Ly`: if the content of the register numbered `n` is greater than 0, then decrement it and jump to the instruction labelled `x`, otherwise jump to the instruction instruction labelled `y`.
  - `HALT`: halt the register machine

For example: `DECC 3 4 5` signifies if register 3's value is greater then 0 decrement it and jump to instruction 4, else jump to instruction 5. More example algorithms written in this instruction format can be found in `addition.txt`, `multiplication.txt`, `trunc_subtraction.txt`. 

In this format, each line stands for each labelled instruction, i.e. the first line is instruction 0, the second line is instruction 1, and so on. Additionally, we treat R0 as the output register, that is when the algorithm halts, the content of that register is the output of the algorithm. 

With `register_machine`, you can construct a register machine by passing in a file pointer to read the test file containing the instructions; output the result of computation with a given register machine and initial input registers (and the maximum number of instructions to be executed); and destruct the register machine by freeing its memory. 

The `main` function in `main.c` takes a file name (containing the instructions) and initial register values (any unprovided register values will be defaulted to 0 in `output_result`) and prints the output if the register machine halts. An example usage would be: `./regmac addition.txt 0 3 4` which should hopefully print 7. Note: you need to provide R0's initial value as done here; of course, you can set it to any natural number you want (since you can always find an equivalent register machine)!

You may wish to write a few register machine instruction lists yourself. Here is a few suggestions:
  - integer division
  - integer remainder
  - exponentiation base 2
  - logarithm base 2
