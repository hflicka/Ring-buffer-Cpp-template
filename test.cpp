
#include <algorithm>
#include <stdio.h>

#include "ringbuffer.h"

#define DATALEN 100000
#define SIZE 10

#define ASSERT(cond) do { if (!(cond)) {printf("assertion \"%s\" failed\n", #cond); exit(1); }} while (0)

int main() {	
	ringbuffer<int> buf(SIZE);
	int databuf[SIZE];
	int readbuf[SIZE];
	int data[DATALEN];
		
	for (int i = 0; i < DATALEN; i++) {
		data[i] = rand();		
	}
	
	srand(123);
	int readindex = 0;
	int i = 0;
	while (readindex < DATALEN) {
		//printf("free: %d\n", buf.getFree());
		size_t wcount = rand() % SIZE;
		for (int j = 0; j < wcount; j++) {
			databuf[j] = data[i];
			i++;
		}
		i -= wcount;
		wcount = std::min(wcount, buf.getFree());
		wcount = std::min(wcount, (size_t)(DATALEN - i));
		i += wcount;		
		size_t x = buf.write(databuf, wcount);
		ASSERT(x == wcount);
		//printf("free: %d\n", buf.getFree());
		
		int rcount = rand() % SIZE;
		x = buf.read(readbuf, rcount);
		for (int j = 0; j < x; j++) {			
			ASSERT(readbuf[j] == data[readindex + j]);
		}
		readindex += x;
	}
	
	return 0;
}
