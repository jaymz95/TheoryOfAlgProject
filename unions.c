#include <stdio.h>  
#include <inttypes.h>

union endian {
	uint8_t ei[2];
	uint16_t si;
};

int main (int argc, char *argv[]) {

	union endian myunion;

	myunion.si = 0xff;

	return 0;
}
