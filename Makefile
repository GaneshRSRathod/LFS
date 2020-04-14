lsync:spinlock.o semaphore.o sleeplock.o rwlock.o condition_variable.o
	ar rcs lsync spinlock.o semaphore.o sleeplock.o rwlock.o condition_variable.o
spinlock.o:spinlock.c synchronization.h
	gcc  -c spinlock.c
semaphore.o:semaphore.c synchronization.h
	gcc -c semaphore.c
sleeplock.o:sleeplock.c synchronization.h
	gcc -c sleeplock.c
rwlock.o:rwlock.c synchronization.h
	gcc -c rwlock.c
condition_variable.o:condition_variable.c synchronization.h
	gcc -c condition_variable.c

