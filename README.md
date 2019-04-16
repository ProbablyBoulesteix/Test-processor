# Test-processor
This is a simple 8 bit Von neumann processor simulator written in C. I designed the ISA to be simple, not to be efficient. It is big-endian.
This project has no definitive purpose: I started it to practice writing CPU emulators before i move on to the 6502/z80 as well as as a way to get more experience with C.

This processor has 5 8-bit GPRs, noted (a,b,c,d and e) as well as an 8bit PC. These registers are given the IDs 00,01,02,03,04 and 05 respectively.
The processor has access to a 256 byte address space. Address 0xFF has a special significance however: jumping to this address will halt the processor and terminate the running program.
Note: all values are treated an unsigned 8bit (char) values.

There is currently no assembler for the processor. Programs have to be written in hex through a hex editor.
This binary file then needs to be named "testprogram.bin" and put in the same directory as the main code.

Register, opcode and address fields are all 8 bits wide.

The processor support 7 different instructions:  // replace $rd,$rs and $rt fields with the appropriate register IDs.
- a NOP instruction, with opcode 0x00. Does nothing and is one byte long (no additionnal parameters).
- an ADD instruction, with opcode 0x01. Syntax: opcode,$rs,$t,$rd.Is 4 bytes long.       //rd= rs+ rt
- a subtract instruction, with opcode 0x02. Syntax opcode,$rs,$t,$rd.Is 4 bytes long.      //rd = rs - rt
- A Jump instruction, with opcode 0x03. Syntax: opcode, target address. 2 bytes long.
- A conditionnal branch instruction, with opcode 0x04. It branches to the target address if rs<rt and falls through otherwise. Syntax: opcode,$rs,$rt,target. 4 bytes long.
- A register-memory Load instruction, with opcode 0x05. Takes the value present at the designated address and loads it into the designated register. Syntax: opcode,$rs,address. 3 bytes long.
- A register-memory Store instruction, with opcode 0x06. Takes the value from the designtaed register and loads it into memory at designated address. Syntax: opcode,$rs,address. 3 bytes long.



Instruction examples:
- Load a,0xFF would be 05 00 FF
- ADD c = a + b would be 01 00 01 02
- JMP 0xAE would be 03 AE
- Branch LT a,b,0xAA would be 04 00 01 AA

This is fairly Generic C89 and has no platform specific calls. It should be able to run in any OS. 

Written by Luc Boulesteix
