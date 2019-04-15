#include <stdio.h>
#include <stdlib.h>

unsigned char address[256];

unsigned char decode(unsigned char pc);
unsigned char registers[6]; // index 0-4 are registers a through e. Index 5 is PC.
int broken();

int main()
{
   //read in program and load into address space
   FILE *ptr;
   ptr = fopen("testprogram.bin","rb");
   fread(address,sizeof(address),1,ptr);



   for (int i = 0;i<6;i++){registers[i] = 0;} //zero out registers and PC.

   while(registers[5]<0xFF){                  //PC $FF ends the computation.
        registers[5] = decode(registers[5]); //PC is sent to main execution loop
   }
printf("Program terminated\n");
printf("Register state : ");
printf("PC is ");printf("%x",registers[5]);printf("\n");
printf("A is ");printf("%x",registers[0]);printf("\n");
printf("B is ");printf("%x",registers[1]);printf("\n");
printf("C is ");printf("%x",registers[2]);printf("\n");
printf("D is ");printf("%x",registers[3]);printf("\n");
printf("E is ");printf("%x",registers[4]);printf("\n");

return 0;

}

unsigned char decode(unsigned char pc){
    unsigned char buffer[3]; //buffer for subsequent bytes
    unsigned char opcode = address[pc];
switch (opcode){
case 0x00:              //NOP
    return (pc+1);
case 0x01:              //ADD
    for (int i = 0;i<3;i++){buffer[i] = address[pc+(i+1)];}
    registers[(buffer[2])] = registers[(buffer[0])] + registers[(buffer[1])];
    return (pc+4);
case 0x02:              //subtract
    for (int i = 0;i<3;i++){buffer[i] = address[pc+(i+1)];}
    registers[(buffer[2])] = registers[(buffer[0])] - registers[buffer[1]];
    return (pc+4);
case 0x03:              //Jump
    buffer[0] = address[pc+1];
    return buffer[0];
case 0x04:              //Branch
    for (int i = 0;i<3;i++){buffer[i] = address[pc+(i+1)];}
    if (registers[buffer[0]] < registers[buffer[1]]) {return buffer[2];}
    else {return (pc+4);}
case 0x05:              //Load address
    for (int i = 0;i<2;i++){buffer[i] = address[pc+(i+1)];}
    registers[buffer[0]] = address [buffer[1]];
    return (pc+3);
case 0x06:              // Store address
    for (int i = 0;i<2;i++){buffer[i] = address[pc+(i+1)];}
    address[buffer[1]] = registers[buffer[0]];
    return (pc+3);

default:
    broken();
    return 0xFF;
}
}

int broken(){
printf("Program terminated due to illegal opcode, error\n");
printf("Register state : ");
printf("Error PC is "); printf("%x",registers[5]);printf("\n");
printf("A is "); printf("%x",registers[0]);printf("\n");
printf("B is "); printf("%x",registers[1]);printf("\n");
printf("C is "); printf("%x",registers[2]);printf("\n");
printf("D is "); printf("%x",registers[3]);printf("\n");
printf("E is "); printf("%x",registers[4]);printf("\n");
return 1;
}
