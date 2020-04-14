#include<pthread.h>
typedef struct data {
	pthread_cond_t cond;
	pthread_mutex_t lock;
}data;

typedef struct semaphore {
	int sp;
	int sl;
	struct data d;
	int waiting;
}semaphore;
typedef struct rwlock {
	int active; //-1 for a writer and number of readers o if available
	struct data d;
	int waitingreaders;
	int waitingwriters;
	int sl;
}rwlock;

typedef struct sleeplock_t {
	int sl;
	int waiting;
	struct data d;
	int sp;
}sleeplock_t;

typedef struct condition {
	int sl;
	struct data d;
	int waiting;
}condition;
	
void spinlock(int *s);
void spinunlock(int *s);
void initspinlock(int *s);
int test_and_set(int *t);
void initsemaphore(struct semaphore *s, int val);
void wait(struct semaphore *s);
void signal(struct semaphore *s);
void block(struct semaphore *s);
void stopsemaphore(struct semaphore *s);
void initrwlock(struct rwlock *r);
void rwblock(struct rwlock *s);
void lockshared(struct rwlock *r);
void unlockshared(struct rwlock *r);
void lockexclusive(struct rwlock *r);
void unlockexclusive(struct rwlock *r);
void stoprwlock(struct rwlock *r);
void stopsleeplock(struct sleeplock_t *s);
void sleepunlock(struct sleeplock_t *s);
void sleeplock(struct sleeplock_t *s);
void initsleeplock(struct sleeplock_t *s);
void initcondition(struct condition *c);
void wait_condition(struct condition *c);
void signal_one(struct condition *c);
void signal_all(struct condition *c);
void stopcondition(struct condition *c);
