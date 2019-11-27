#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PG_SIZE 4096
#define DEBUG 0

int main(int argc, char *argv[]){


	int i;
	char *val[20];

	for (i = 0; i < 12; ++i) {
		val[i] = sbrk(PG_SIZE);
		printf(1, "val[%d]=0x%x\n", i, val[i]);

        if(i==12){
            printf(1, "Called sbrk(PG_SIZE) 12 times - all physical pages taken.\nPress any key...\n");
            val[12] = sbrk(PG_SIZE);
            printf(1, "val[12]=0x%x\n", val[12]);
        }
	}

	return 0;
}
