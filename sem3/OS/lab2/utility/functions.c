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
    if (*count_threads <= 0) {
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

