#include "utility.h"

error_msg init(int *msg_id_1, int *msg_id_2) {
	if (!msg_id_1 || !msg_id_2) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	key_t tmp_key1 = ftok(TOKEN, PROJECT_ID_KEY_1);
	if (tmp_key1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}

	int tmp_msg_1 = msgget(tmp_key1, IPC_CREAT | 0666);
	if (tmp_msg_1 == -1) {
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	key_t tmp_key2 = ftok(TOKEN, PROJECT_ID_KEY_2);
	if (tmp_key2 == -1) {
		msgctl(tmp_msg_1, IPC_RMID, 0);
		return (error_msg){TOKEN_ERROR, __func__, "ftok"};
	}

	int tmp_msg_2 = msgget(tmp_key2, IPC_CREAT | 0666);
	if (tmp_msg_2 == -1) {
		msgctl(tmp_msg_1, IPC_RMID, 0);
		return (error_msg){TOKEN_ERROR, __func__, "msgget"};
	}

	*msg_id_1 = tmp_msg_1;
	*msg_id_2 = tmp_msg_2;
	return (error_msg){SUCCESS, "", ""};
}




error_msg processing_paths(StringVector *input, StringVector **output_t) {
	if (!input || !output_t) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	StringVector * output;
	DirEntry *dirs = malloc(input->size * sizeof(DirEntry));
	if (!dirs) {
		return (error_msg){MEMORY_ALLOCATED_ERROR, __func__, "memoy allocated error"};
	}
	size_t dir_count = 0;
	error_msg errorMsg;
	for (size_t i = 0; i < input->size; i++) {

		char dir[FILENAME_MAX];
		memset(dir, '\0', FILENAME_MAX);


		char file[FILENAME_MAX];
		memset(file, '\0', FILENAME_MAX);

		int index = 0;
		for(int k = 0; input->data[i][k]; ++k) {
			if(input->data[i][k] == '/') {
				index = k;
			}
		}

		strcopy(input->data[i], dir, 0, index);
		strcopy(input->data[i], file, index + 1, strlen(input->data[i]));


		size_t found = 0;
		for (size_t j = 0; j < dir_count; j++) {
			if (strcmp(dirs[j].dir, dir) == 0) {
				errorMsg = push_end_string_vector(dirs[j].files, file);
				if (errorMsg.type) {
					for (int k = 0; k < dir_count; ++k) {
						destroy_string_vector(dirs[k].files);
					}
					free(dirs);
					return errorMsg;
				}
				found = 1;
				break;
			}
		}
		if (!found) {
			strncpy(dirs[dir_count].dir, dir, FILENAME_MAX);
			dirs[dir_count].files = create_string_vector(1);
			if (!dirs[dir_count].files) {
				for (int k = 0; k < dir_count; ++k) {
					destroy_string_vector(dirs[k].files);
				}
				free(dirs);
				return (error_msg){MEMORY_ALLOCATED_ERROR, __func__ , "create_string vector"};
			}
			errorMsg = push_end_string_vector((dirs[dir_count].files), file);
			if (errorMsg.type) {
				for (int k = 0; k < dir_count; ++k) {
					destroy_string_vector(dirs[k].files);
				}
				free(dirs);
				return errorMsg;
			}
			dir_count++;
		}
	}

	output = create_string_vector(1);
	if (!output) {
		for (int k = 0; k < dir_count; ++k) {
			destroy_string_vector(dirs[k].files);
		}
		free(dirs);
		return (error_msg){MEMORY_ALLOCATED_ERROR, __func__ , "create_string vector"};
	}

	for (size_t i = 0; i < dir_count; i++) {
		errorMsg = push_end_string_vector(output, dirs[i].dir);
		if (errorMsg.type) {
			for (int k = 0; k < dir_count; ++k) {
				destroy_string_vector(dirs[k].files);
			}
			destroy_string_vector(output);
			free(dirs);
			return errorMsg;
		}

		for (size_t j = 0; j < dirs[i].files->size; j++) {
			errorMsg = push_end_string_vector(output, dirs[i].files->data[j]);
			if (errorMsg.type) {
				for (int k = 0; k < dir_count; ++k) {
					destroy_string_vector(dirs[k].files);
				}
				free(dirs);
				destroy_string_vector(output);
				return errorMsg;
			}
		}
	}
	for (int k = 0; k < dir_count; ++k) {
		destroy_string_vector(dirs[k].files);
	}
	free(dirs);
	*output_t = output;
	return (error_msg){SUCCESS, "", ""};
}
