#include "utility/functions.h"


pthread_mutex_t mutex;


void *game_manager(void *arg) {
    Thread_data *data = (Thread_data *) arg;
    int current_round = data->current_round;
    int total_points_player1 = data->total_points_player1;
    int total_points_player2 = data->total_points_player2;
    int count_games_all = data->count_games_all;
    int count_experiments = data->count_experiments;

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

    pthread_mutex_lock(&mutex);
    data->results[0] += local_res[0];
    data->results[1] += local_res[1];

    pthread_mutex_unlock(&mutex);

    free(data);
    return NULL;
}

int main(int argc, char **argv) {
    // Получение и валидация
    int count_threads = 0;
    int count_games_all = 0;
    int current_round = 0;
    int total_points_player1 = 0;
    int total_points_player2 = 0;
    int count_experiments = 0;
    error_msg errorMsg = get_ops(argc, argv, &count_threads, &count_games_all, &current_round,
                                 &total_points_player1,
                                 &total_points_player2, &count_experiments);
    if (errorMsg.type) {
        return print_error(errorMsg);
    }

    pthread_t threads[count_threads];
//    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);

    int count_exp_per_thread = count_experiments / count_threads;
    int remaining_experiments = count_experiments % count_threads;

    int results[2] = {0, 0};

    for (int i = 0; i < count_threads; ++i) {
        Thread_data *data = (Thread_data *) malloc(sizeof(Thread_data));
        data->results = results;
        data->count_games_all = count_games_all;
        data->current_round = current_round;
        data->total_points_player1 = total_points_player1;
        data->total_points_player2 = total_points_player2;
        data->count_experiments = count_exp_per_thread + (i < remaining_experiments ? 1 : 0);

        pthread_create(&threads[i], NULL, game_manager, (void *) (data));
    }

    // Синхронизируем
    for (int i = 0; i < count_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Player 1: %d\n", results[0]);
    printf("Player 2: %d\n", results[1]);
    printf("Draws: %d\n", count_experiments - results[0] - results[1]);


    pthread_mutex_destroy(&mutex);
    return 0;
}
