# CustomCPU
A simple 16 bit CPU emulator based on a CPU design from a lab in Pitt's CS0447 course

## Makefile options:
   * debug
       * For debugging (surprising right?)
   * final
       * Sort of a "distribution" build with default linking
   * static32
       * A build with statically linked libraries for 32-bit systems
   * static64
       * A build with statically linked libraries for 64-bit systems
## OpCodes
  * set: 0x0
  * add: 0x2
  * sub: 0x3
  * or:  0x4
  * and: 0x5
  * lm:  0x8
  * sm:  0x9
  * jmp: 0xB
  * beq: 0xF
  * bne: 0x7
  * fnc: 0x6
