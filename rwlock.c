#include"synchronization.h"

void initrwlock(struct rwlock *r) {
	r->active = 0;
	r->d.cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	r->d.lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&r->d.lock);
	initspinlock(&r->sl);
	r->waitingreaders = 0;
	r->waitingwriters = 0;
}
void rwblock(struct rwlock *s) {
	spinunlock(&s->sl);
	pthread_cond_wait(&s->d.cond, &s->d.lock);
}
	

void lockshared(struct rwlock *r) {
	spinlock(&r->sl);
	(r->waitingreaders)++;
	while(r->active < 0) {
		rwblock(r);
		spinlock(&r->sl);
	}
	(r->waitingreaders)--;
	(r->active)++;
	spinunlock(&r->sl);
}

void unlockshared(struct rwlock *r) {
	spinlock(&r->sl);
	(r->active)--;
	if(!(r->active)) {
		spinunlock(&r->sl);
		pthread_cond_broadcast(&r->d.cond);
	}
	else
		spinunlock(&r->sl);
}
	
void lockexclusive(struct rwlock *r) {
	spinlock(&r->sl);
	(r->waitingwriters)++;
	while(r->active) {
		rwblock(r);
		spinlock(&r->sl);
	}
	(r->waitingwriters)--;
	r->active = -1;
	spinunlock(&r->sl);
}
void unlockexclusive(struct rwlock *r) {
	spinlock(&r->sl);
	r->active = 0;
	pthread_cond_broadcast(&r->d.cond);
	spinunlock(&r->sl);
}

void stoprwlock(struct rwlock *r) {
	spinlock(&r->sl);
	while(r->waitingwriters || r->waitingreaders) {
		spinunlock(&r->sl);
		pthread_mutex_unlock(&r->d.lock);
		spinlock(&r->sl);
	}
	spinunlock(&r->sl);
}
		
