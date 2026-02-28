# intel4004-asm (In progress)
The assembler for my intel 4004 emulator. [Emulator repo](https://github.com/PinkFlowerDelivery/intel4004-emulator)

## How to build 
```
git clone https://github.com/PinkFlowerDelivery/intel4004-asm
cd intel4004-asm 
mkdir build 
cmake -S . -B ./build
cmake --build build

./build/i4004asm path/to/program.asm 
```

## Custom instructions
**store** - [register pair; 8-bit address]  
Stores the value from the specified register pair into ROM at the given 8-bit address.  
Used by the FIM and FIN instructions.

## Usage example 
```
main: ldm 10 ; Load 10 to AC
xch r1       ; Move value from AC to r1 register
ldm 5        ; Load 5 to AC
add r1       ; Add AC and r1 register
jun main     ; Jump to label main
```


