#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

#define KEY 78

int main(int argc, char *argv[]) {
    int sem_value = 0;
    int sem;
    int amt = 1;

    if (argc > 2) {
        sem_value = atoi(argv[2]);
        if (sem_value < 1) {
            printf("Semaphore amount must be >0\n");
            return 0;
        }

        sem = semget(KEY, amt, IPC_CREAT | IPC_EXCL | 0600);
        if (sem == -1) {
            printf("Semaphore already exists\n");
            return 0;
        }

        printf("semaphore created: %d\n", sem);
        semctl(sem, 0, SETVAL, sem_value);
        printf("value set: %d\n", sem_value);
        return 0;
    }

    if (strcmp(argv[1], "-v") == 0) {
        sem = semget(KEY, amt, 0600);
        if (sem == -1) {
            printf("%s\n", strerror(errno));
            return 0;
        }
        int val = semctl(sem, 0, GETVAL);
        printf("semaphore value: %d\n", val);
        return 0;
    }

    if (strcmp(argv[1], "-r") == 0) {
        sem = semget(KEY, amt, 0600);
        if (sem == -1) {
            printf("%s\n", strerror(errno));
            return 0;
        }

        int val = semctl(sem, 0, IPC_RMID);
        printf("semaphore removed: %d\n", sem);
        return 0;
    }

    printf("Invalid argument\n");
    return 0;

}
