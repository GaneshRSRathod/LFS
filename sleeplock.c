#include"synchronization.h"
#include<stdatomic.h>

void initsleeplock(struct sleeplock_t *s) {
	s->sp = 0;
	s->waiting = 0;
	initspinlock(&s->sl);
	s->d.cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	s->d.lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&s->d.lock);
}
void sleeplock(struct sleeplock_t *s) {
	spinlock(&s->sl);
	(s->waiting)++;
	spinunlock(&s->sl);
	while(atomic_flag_test_and_set(&s->sp) != 0) {
		pthread_cond_wait(&s->d.cond, &s->d.lock);

	}
	spinlock(&s->sl);
	(s->waiting)--;
	spinunlock(&s->sl);
}

void sleepunlock(struct sleeplock_t *s) {
	spinlock(&s->sl);
	s->sp = 0;
	pthread_cond_broadcast(&s->d.cond);
	spinunlock(&s->sl);
}

void stopsleeplock(struct sleeplock_t *s) {
	spinlock(&s->sl);
	while(s->waiting) {
		spinunlock(&s->sl);
		pthread_mutex_unlock(&s->d.lock);
		spinlock(&s->sl);
	}
	spinunlock(&s->sl);
}

