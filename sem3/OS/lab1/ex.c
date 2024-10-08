#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int CharToDouble(const char* string, double* result) {
    int k = -1;
    int fl = 0;
    double number = 0;
    for (int j = 0; string[j] != '\0'; ++j) {
        if (string[j] == '-' && fl == 0)
            fl = 1;
        else if (string[j] >= '0' && string[j] <= '9') {
            number *= 10;
            number += (string[j] - '0');
            if (k != -1) k += 1;
        } else if (string[j] == '.' && k == -1)
            k = 0;
        else {
            return 1;
        }
    }
    for (int k_null = 0; k_null < k; ++k_null) number /= 10.0;
    k = -1;
    if (fl) number *= -1;
    // putchar('\n');
    // printf("%f\n", number);
    *result = number;
    return 0;
}


int main() {
    float sum = 0.0;
    char buffer[4096];
    ssize_t n;
    while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        char *ptr = buffer;
        char *token;
        while ((token = strtok(ptr, " ")) != NULL) {
            double num = 0;
            if(CharToDouble(token, &num)){
                const char msg[] = "error: unrecognized character\n";
                write(STDERR_FILENO, msg, sizeof (msg));
                exit(EXIT_FAILURE);
            }
            sum += num;
            ptr = NULL;
        }
    }


    char output[1024];
    snprintf(output, sizeof(output), "%f\n", sum);


    int32_t written = write(STDOUT_FILENO, output, strlen(output));
    if (written != strlen(output)) {
        const char msg[] = "error: failed to write to file\n";
        write(STDERR_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
    return 0;
}