#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <stdio.h>

/**
 * 7 вариант) В файле записаны команды вида: «число число число<endline>». Дочерний процесс
считает их сумму и выводит результат в стандартный поток вывода. Числа имеют тип float.
Количество чисел может быть произвольным.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    size_t size = 256;
    char filename[size];
    ssize_t n;
    if((n = read(STDIN_FILENO, filename, size - 2)) < 0){
        exit(EXIT_FAILURE);
    }
    filename[n - 1] = '\0';
    int fd[2];
    if(pipe(fd) < 0){
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid == -1){
        const char msg[] = "error: failed to spawn new process\n";
        write(STDERR_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
//        printf("Process 1: %d\n", getpgid(pid));
        close(fd[0]);
        int file = open(filename, O_RDONLY);
        if(file < 0){
            const char msg[] = "error: input file didn't open\n";
            write(STDERR_FILENO, msg, sizeof(msg));
            exit(EXIT_FAILURE);
        }
        dup2(file, STDIN_FILENO);
        close(file);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execl("./ex.exe", "ex.exe", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else{
//        printf("Process 2: %d\n", getpgid(pid));
        close(fd[1]);
        char buffer[1024];
        ssize_t n;
        while ((n = read(fd[0], buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, n);
        }
        close(fd[0]);
        wait(NULL);
    }

    return 0;
}