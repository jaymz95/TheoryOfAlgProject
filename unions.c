#include <stdio.h>  
#include <inttypes.h>

union endian {
	uint8_t ei[2];
	uint16_t si;
};

int main (int argc, char *argv[]) {

	union endian myunion;

	myunion.si = 0xff;

	printf("16bit: %04" PRIx16 "\n", myunion.si);
	printf(" 8bit: %02" PRIx8 " %02" PRIX8 "\n", myunion.ei[0], myunion.ei[1]);

	return 0;
}
