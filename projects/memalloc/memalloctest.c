#include <stdio.h>
#include <string.h>

#include "threads/thread.h"
#include "threads/malloc.h"
#include "threads/palloc.h"

#include "projects/memalloc/memalloctest.h"

void run_memalloc_test(char **argv UNUSED)
{
	size_t i;
	char* dynamicmem[11];

	dynamicmem[0] = (char *) malloc (110000);
	memset (dynamicmem[0], 0x00, 110000);

	dynamicmem[1] = (char *) malloc (200000);
	memset (dynamicmem[1], 0x00, 200000);

	dynamicmem[2] = (char *) malloc (300000);
	memset (dynamicmem[2], 0x00, 300000);

	dynamicmem[3] = (char *) malloc (140000);
	memset (dynamicmem[3], 0x00, 140000);

	dynamicmem[4] = (char *) malloc (180000);
	memset (dynamicmem[4], 0x00, 180000);

	dynamicmem[5] = (char *) malloc (220000);
	memset (dynamicmem[5], 0x00, 220000);

	printf ("dump page status : \n");
	palloc_get_status (0);

	thread_sleep (100);

	for (i=2; i<6; i=i*2) {
		free(dynamicmem[i]);
		printf ("dump page status : \n");
		palloc_get_status (0);
	}

	for (i=6; i<10; i++) {
		dynamicmem[i] = (char *) malloc (140000);
		memset (dynamicmem[i], 0x00, 140000);
		printf ("dump page status : \n");
		palloc_get_status (0);
	}
}
