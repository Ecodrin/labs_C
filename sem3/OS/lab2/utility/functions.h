
#ifndef LAB2_FUNCTIONS_H
#define LAB2_FUNCTIONS_H

#include "../SystemErrors/errors.h"
#include "utility.h"

#include <unistd.h>
#include "string.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Thread_data {
    pthread_mutex_t* mutex;
    int* results;
    int count_games_all;
    int current_round;
    int total_points_player1;
    int total_points_player2;
    int count_experiments;
    int fl_is_one_thread;
} Thread_data;

error_msg get_ops(int argc, char **argv, int *count_threads, int *count_games_all, int *current_round,
                  int *total_points_player1,
                  int *total_points_player2, int *count_experiments);


void *game_manager(void *arg);

#endif //LAB2_FUNCTIONS_H
