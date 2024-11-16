#include "utility/functions.h"


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
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);

    int count_exp_per_thread = count_experiments / count_threads;
    int remaining_experiments = count_experiments % count_threads;

    int results[2] = {0, 0};

    for (int i = 0; i < count_threads; ++i) {
        Thread_data data = {mutex, results, count_games_all, current_round, total_points_player1, total_points_player2,
                            count_exp_per_thread + (i < remaining_experiments ? 1 : 0)};

        pthread_create(&threads[i], NULL, game_manager, (void*)(&data));
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
