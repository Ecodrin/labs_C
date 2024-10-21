#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int CharToDouble(const char *string, double *result) {
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
        else if (string[j] == '\n')
            break;
        else {
            return 1;
        }
    }
    if (k == 0) return 1;
    for (int k_null = 0; k_null < k; ++k_null) number /= 10.0;
    k = -1;
    if (fl) number *= -1;
    // putchar('\n');
    *result = number;
    return 0;
}


int main() {
    float sum = 0.0;
    char output[4096];
    char input[4096];
    output[0] = '\0';
    char c;
    char buffer[1024];
    int i = 0;
    int j = 0;
    ssize_t n;
    double num = 0;
    while ((n = read(STDIN_FILENO, input, sizeof(input))) > 0){
        j = 0;
        while ((c = input[j++]) != '\0' ) {
            if (c == ' ' && i != 0) {
                num = 0;
                buffer[i] = '\0';
                if (CharToDouble(buffer, &num)) {
                    const char msg[] = "error: unrecognized character\n";
                    write(STDERR_FILENO, msg, sizeof(msg));
                    exit(EXIT_FAILURE);
                }
                i = 0;
                sum += (float) num;
            } else if (c == '\n') {
                num = 0;
                buffer[i] = '\0';
                if (CharToDouble(buffer, &num)) {
                    const char msg[] = "error: unrecognized character\n";
                    write(STDERR_FILENO, msg, sizeof(msg));
                    exit(EXIT_FAILURE);
                }
                sum += (float) num;
                sprintf(output + strlen(output), "%f\n", sum);
                sum = 0;
                i = 0;
            } else {
                buffer[i++] = c;
            }
        }
        if (i != 0) {
            buffer[i] = '\0';
            if (CharToDouble(buffer, &num)) {
                const char msg[] = "error: unrecognized character\n";
                write(STDERR_FILENO, msg, sizeof(msg));
                exit(EXIT_FAILURE);
            }
            sum += (float) num;
            sprintf(output + strlen(output), "%f\n", sum);
        }
    }

    size_t written = write(STDOUT_FILENO, output, strlen(output));
    if (written != strlen(output)) {
        const char msg[] = "error: failed to write to output\n";
        write(STDERR_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
    return 0;
}