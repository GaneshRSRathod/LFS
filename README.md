# LFS
#Synchronization Library

The Linux From Scratch project is done. The image of the console is uploaded.

Synchronization library :
  Synchronization library is created for synchronizing threads.

1. Spinlock :
    Spinlock is implemented on a shared int value. It is done using atomic_flag_test_and_set function  of linux library stdatomic.
    Functions:
    initspinlock(int*): Initialize spinlock.
    spinlock(int*): aquiring a spinlock
    spinunlock(int*); releasing spinlock
    
2. Semaphore :
    Semaphore is implemented using spinlock library developed in the project and the pthread_mutex. Semaphore is implemented on sharred structure semaphore.
    Functions:
    initsemaphore(semaphore*,int*): Initialize semaphore to value passed.
    wait(semaphore*): for aquiring lock on the data
    signal(semaphore*):for realising the lock aquired
    stopsemaphore(semaphore*): It should be run to stop the semaphore. It unlocks all the locks and waits active for pthread_mutex.
    
 3. Sleeplock :
     Sleeplock is implemented using spinlock and pthread_mutex. It is implemented on shared structure sleeplock_t.
     Functions:
     initsleeplock(sleeplock_t*): Initialise the sleeplock.
     sleeplock(sleeplock_t*): to aquire a sleeplock.
     sleepunlock(sleeplock_t*): to release a sleeplock.
     stopsleeplock(sleeplock_t*): for stopping the sleeplock. It unlocks all the loocks and watis active for pthread_mutex.
     
 4.Read Write Lock:
    Read Write Lock is implemented using spinlock and pthread_mutex on shared structure rwlock.
    Functions:
    initrwlock(rwlock*): initializing read write lock.
    lockshared(rwlock*): aquiring reading lock.
    unlockshared(rwlock*): realeasing reader lock.
    lockexclusive(rwlock*): aquiring writer lock.
    unlockexclusive(rwlock*): releasing writer lock.
    stoprwlock(rwlock*): for stopping read write lock. It unlocks all the locks and waits active for phtread_mutex.
    
  5.Condition variables:
    It is implemented using spinlock and pthread mutex on shared structure condition.
    Functions:
    initcondition(condition*): Initialising condition variable.
    wait_condition(condition*): to go to wait state.
    signal_one(condition*): for signaling a waiting thread to start.
    signal_all(condition*): for signaling all wating threads to start.
    stopcondition(condition*): for stopping condition variables. It unlocks all the locks and wats active for pthread_mutex. 
