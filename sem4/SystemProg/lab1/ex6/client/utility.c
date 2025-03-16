#include "utility.h"

error_msg init(int *msg_id_1, int *msg_id_2) {
	if (!msg_id_1 || !msg_id_2) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	key_t tmp_key1 = ftok(TOKEN, PROJECT_ID_KEY_1);
	if (tmp_key1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}

	int tmp_msg_1 = msgget(tmp_key1, 0666);
	if (tmp_msg_1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	key_t tmp_key2 = ftok(TOKEN, PROJECT_ID_KEY_2);
	if (tmp_key2 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}

	int tmp_msg_2 = msgget(tmp_key2, 0666);
	if (tmp_msg_2 == -1) {
		msgctl(tmp_msg_1, IPC_RMID, 0);
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	*msg_id_1 = tmp_msg_1;
	*msg_id_2 = tmp_msg_2;
	return (error_msg){SUCCESS, "", ""};
}