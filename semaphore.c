#include"synchronization.h"

void initsemaphore(struct semaphore *s, int val) {
	s->sp = val;
	initspinlock(&s->sl);
	s->d.cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	s->d.lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&s->d.lock);
	s->waiting = 0;

}
void block(struct semaphore *s) {
	spinunlock(&s->sl);
	pthread_cond_wait(&s->d.cond, &s->d.lock);
}
	

void wait(struct semaphore *s) {
	spinlock(&s->sl);
	(s->waiting)++;
	while(s->sp <= 0) {
		block(s);
		spinlock(&s->sl);
	}
	(s->waiting)--;
	(s->sp)--;
	spinunlock(&s->sl);
}
void signal(struct semaphore *s) {
	spinlock(&s->sl);
	(s->sp)++;
	pthread_cond_broadcast(&s->d.cond);
	spinunlock(&s->sl);
}

void stopsemaphore(struct semaphore *s) {
	spinlock(&s->sl);
	while(s->waiting) {
		spinunlock(&s->sl);
		pthread_mutex_unlock(&s->d.lock);
		spinlock(&s->sl);
	}
	spinunlock(&s->sl);
}
