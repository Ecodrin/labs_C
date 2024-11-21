#include "functions.h"

error_msg get_ops(int argc, char **argv, int *count_threads, int *count_games_all,
                  int *current_round, int *total_points_player1,
                  int *total_points_player2, int *count_experiments) {
    if (argc != 7) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: incorrect count arguments"};
    }

    error_msg errorMsg = char_to_int(argv[1], count_threads);
    if (errorMsg.type) {
        return errorMsg;
    }
    if (*count_threads < 0) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: count_threads must be greater than 0"};
    }

    errorMsg = char_to_int(argv[2], count_games_all);
    if (errorMsg.type) {
        return errorMsg;
    }
    if (*count_games_all < 0) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: count_games_all must be greater than 0"};
    }

    errorMsg = char_to_int(argv[3], current_round);
    if (errorMsg.type) {
        return errorMsg;
    }
    if (*current_round < 0) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: current_round must be greater than 0"};
    }


    errorMsg = char_to_int(argv[4], total_points_player1);
    if (errorMsg.type) {
        return errorMsg;
    }
    if (*total_points_player1 < 0) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: total_points_player1 must be greater than 0"};
    }


    errorMsg = char_to_int(argv[5], total_points_player2);
    if (errorMsg.type) {
        return errorMsg;
    }
    if (*total_points_player2 < 0) { ;
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: total_points_player2 must be greater than 0"};
    }

    errorMsg = char_to_int(argv[6], count_experiments);
    if (errorMsg.type) {
        return errorMsg;
    }
    if (*count_experiments < 0) {
        return (error_msg) {INCORRECT_OPTIONS_ERROR, "Error - get_ops: count_experiments must be greater than 0"};
    }


    return (error_msg){SUCCESS, ""};

}


void *game_manager(void *arg) {
    Thread_data *data = (Thread_data *) arg;
    pthread_mutex_t *mutex = data->mutex;
    int current_round = data->current_round;
    int total_points_player1 = data->total_points_player1;
    int total_points_player2 = data->total_points_player2;
    int count_games_all = data->count_games_all;
    int count_experiments = data->count_experiments;
    int fl_is_one_thread = data->fl_is_one_thread;

    int local_res[2] = {0, 0};
    for (int i = 0; i < count_experiments; ++i) {
        int points_player1 = total_points_player1;
        int points_player2 = total_points_player2;
        for (int j = current_round; j < count_games_all; ++j) {
            int dice1 = rand() % 6 + 1;
            int dice2 = rand() % 6 + 1;
            points_player1 = dice1 + dice2;

            dice1 = rand() % 6 + 1;
            dice2 = rand() % 6 + 1;
            points_player2 = dice1 + dice2;
        }

        if (points_player1 > points_player2) {
            local_res[0] += 1;
        } else if (points_player2 > points_player1) {
            local_res[1] += 1;
        }
    }

    if(!fl_is_one_thread)
        pthread_mutex_lock(mutex);
    data->results[0] += local_res[0];
    data->results[1] += local_res[1];
    if(!fl_is_one_thread)
        pthread_mutex_unlock(mutex);

    free(data);
    return NULL;
}