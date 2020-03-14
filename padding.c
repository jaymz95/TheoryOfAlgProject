// James Mullarkey
//

#include <stdio.h>
#include <inttypes.h>


int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Error: expected single filename as argument.\n");
		return 1;
	}

	FILE *infile = fopen(argv[1], "rb");
	if (!infile) {
		printf("Error: couldn't open file %s.\n", argv[1]);
		return 1;
	}

	fclose(infile);

	return 0;
}
