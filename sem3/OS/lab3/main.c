#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/wait.h>

#include "SystemErrors/errors.h"


const char SHARED_MEM_NAME[] = "/shared_memory_example";
const int SHARED_MEM_SIZE = 4096;

const char SEM_NAME[] = "/my_semaphore";

int main(void) {

    size_t size = 4096;
    char filename[size];
    ssize_t n;
    if ((n = read(STDIN_FILENO, filename, size - 2)) < 0) {
        return print_error((error_msg) {INCORRECT_OPTIONS_ERROR, "main", "didn't read filename"});
    }
    filename[n - 1] = '\0';


    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        return print_error((error_msg) {INPUT_FILE_ERROR, "main", "shm fd didn't open"});
    }

    if (ftruncate(shm_fd, SHARED_MEM_SIZE)) {
        shm_unlink(SHARED_MEM_NAME);
        return print_error((error_msg) {INPUT_FILE_ERROR, "main", "size shared memory didn't set"});
    }

    char *shared_mem = (char *) mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        shm_unlink(SHARED_MEM_NAME);
        return print_error((error_msg) {INPUT_FILE_ERROR, "main", "mmap didn't work"});
    }

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
        shm_unlink(SHARED_MEM_NAME);
        munmap(shared_mem, SHARED_MEM_SIZE);
        return print_error((error_msg) {INPUT_FILE_ERROR, "main", "semaphore didn't create"});
    }

    pid_t pid = fork();
    if (pid < 0) {
        return print_error((error_msg) {INCORRECT_OPTIONS_ERROR, "main", "fork error"});
    } else if (pid == 0) {
        int fd;

        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            sem_close(sem);
            shm_unlink(SEM_NAME);
            shm_unlink(SHARED_MEM_NAME);
            munmap(shared_mem, SHARED_MEM_SIZE);
            return print_error((error_msg) {INPUT_FILE_ERROR, "main", "can't open file"});
        }


        if (dup2(fd, STDIN_FILENO) == -1) {
            sem_close(sem);
            shm_unlink(SEM_NAME);
            shm_unlink(SHARED_MEM_NAME);
            munmap(shared_mem, SHARED_MEM_SIZE);
            return print_error((error_msg) {INPUT_FILE_ERROR, "main", "can't dup2 file"});
        }
        close(fd);

        execl("./child", "child", NULL);

        exit(EXIT_FAILURE);

    } else {


        sem_wait(sem);

        write(STDOUT_FILENO, shared_mem, strlen(shared_mem));


        munmap(shared_mem, SHARED_MEM_SIZE);
        shm_unlink(SHARED_MEM_NAME);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        wait(NULL);
    }

    return 0;
}
