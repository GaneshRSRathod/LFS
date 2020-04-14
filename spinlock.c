#include"synchronization.h"
#include<stdatomic.h>
void spinlock(int *s) {
	while(atomic_flag_test_and_set(s) != 0)
		while(*s != 0);
}
void spinunlock(int *s) {
	*s = 0;
}
void initspinlock(int *s) {
	*s = 0;
}
