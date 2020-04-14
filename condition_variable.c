#include"synchronization.h"

void initcondition(struct condition *c) {
	initspinlock(&c->sl);
	c->waiting = 0;
	c->d.cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	c->d.lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&c->d.lock);
}

void wait_condition(struct condition *c) {
	spinlock(&c->sl);
	(c->waiting)++;
	spinunlock(&c->sl);
	pthread_cond_wait(&c->d.cond, &c->d.lock);
	spinlock(&c->sl);
	(c->waiting)--;
	spinunlock(&c->sl);
}
void signal_one(struct condition *c) {
	spinlock(&c->sl);
	pthread_cond_signal(&c->d.cond);
	spinunlock(&c->sl);
}
void signal_all(struct condition *c) {
	spinlock(&c->sl);
	pthread_cond_broadcast(&c->d.cond);
	spinunlock(&c->sl);
}
void stopcondition(struct condition *c) {
	spinlock(&c->sl);
	while(c->waiting) {
		spinunlock(&c->sl);
		pthread_mutex_unlock(&c->d.lock);
		spinlock(&c->sl);
	}
	spinunlock(&c->sl);
}

