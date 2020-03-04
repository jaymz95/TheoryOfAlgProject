#include <stdio.h>
#include <stdint.h>

//section 4.1.2
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) ^ (!x & z);
}

int main(int argc, char *argv[]) {
    uint32_t x = 0x0f0f0f0f;
    uint32_t y = 0xcccccccc;
    uint32_t z = 0x55555555;

    printf("x = %x\n", x);
    printf("y = %x\n", y);
    printf("z = %x\n", z);

    printf("Ch(x,y,z) = %x\n", Ch(x, y, z));

    return 0;
}