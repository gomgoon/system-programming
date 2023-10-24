#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	printf("page size: %ld btyes\n", sysconf(_SC_PAGESIZE)); // 4096 bytes on x64
	exit(EXIT_SUCCESS);
}
