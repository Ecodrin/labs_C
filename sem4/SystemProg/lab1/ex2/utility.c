#include "utility.h"

/*
 * Основной алгоритм:
 * 1. Считаем 2 ^ n = кол-во битов = block_bits
 * 2. Считаем размер блока в байтах = block_bytes
 * 3. Читаем из файла по block_bytes байт
 * 4. Считаем число из прошлого пункта
 * 5. XOR_F по всем числам
 */
error_msg xor_n(FILE *file, int n, size_t *result) {
	if (file == NULL || result == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	if (n < 2 || n > 6) {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "n should be between 2 and 6"};
	}

	// Узнаем размер файла в байтах
	fseek(file, 0, SEEK_END);
	size_t size_file = ftell(file);
	rewind(file);

	size_t total_bits = size_file * 8;
	const size_t block_bits = 1 << n;
	const size_t block_bytes = block_bits / 8;
	const size_t count_blocks = (total_bits + block_bits - 1) / block_bits;

	size_t val = 0;
	size_t tmp_val;
	unsigned char buf[block_bytes];
	for (size_t i = 0; i < count_blocks; ++i) {
		tmp_val = 0;

		// Читаем block_bytes байт
		size_t real_count_bytes = fread(buf, 1, block_bytes, file);

		if (real_count_bytes < block_bytes) {
			memset(buf + real_count_bytes, 0, block_bytes - real_count_bytes);
		}

		int bit;
		for (int current_bit = 0; current_bit < block_bits; ++current_bit) {
			size_t byte_idx = current_bit / 8;
			size_t bit_idx = 7 - (current_bit % 8);
			bit = (buf[byte_idx] >> bit_idx) & 1;
			tmp_val = (tmp_val << 1) | bit;
		}
		// Сложение по модулю 2
		val ^= tmp_val;
	}

	*result = val;

	return (error_msg){SUCCESS, "", ""};
}

error_msg get_32bit(char *mask, int32_t *res) {
	if (mask == NULL || res == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	char *end_ptr;
	int32_t mask_32bit = (int32_t)strtoul(mask, &end_ptr, 16);
	if (end_ptr == mask || *end_ptr != '\0') {
		return (error_msg){INCORRECT_OPTIONS_ERROR, __func__, "mask isn't correct"};
	}

	*res = mask_32bit;
	return (error_msg){SUCCESS, "", ""};
}

error_msg find_sum_hex(FILE *file, char *mask, int *res) {
	if (file == NULL || mask == NULL || res == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}

	int32_t mask_32bit;
	error_msg errorMsg = get_32bit(mask, &mask_32bit);
	if (errorMsg.type) {
		return errorMsg;
	}

	int count = 0;
	int32_t num;
	String s;
	errorMsg = create_string(&s, "");
	if (errorMsg.type) {
		return errorMsg;
	}
	while (!feof(file)) {
		clear_string(&s);
		errorMsg = safe_read_string(file, &s);
		if (errorMsg.type) {
			destroy_string(&s);
			return errorMsg;
		}
		char *end;

		int32_t num = (int32_t)strtol(s.arr, &end, 10);
		if (end == s.arr || *end != '\0') {
			continue;
		}

		if ((num & mask_32bit) == mask_32bit) {
			count++;
		}
	}

	destroy_string(&s);
	*res = count;
	return (error_msg){SUCCESS, "", ""};
}

error_msg generate_filename(char *filename, int j, char *res) {
	if (filename == NULL || res == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	int k = -1;
	for (int i = 0; i < strlen(filename); i++) {
		if (filename[i] == '.') {
			k = i;
		}
	}

	if (k == -1) {
		sprintf(res, "%s_%d", filename, j);
	} else {
		char tmp1[strlen(filename)];
		char tmp2[strlen(filename)];
		strcopy(filename, tmp1, 0, k);
		strcopy(filename, tmp2, k, strlen(filename));
		sprintf(res, "%s_%d%s", tmp1, j, tmp2);
	}

	return (error_msg){SUCCESS, "", ""};
}

error_msg copy_file(const char *src, const char *dst) {
	if (src == NULL || dst == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	FILE *src_file = fopen(src, "rb");
	if (!src_file) {
		return (error_msg){INPUT_FILE_ERROR, __func__, "input file didn't open"};
	}

	FILE *dst_file = fopen(dst, "wb");
	if (!dst_file) {
		fclose(src_file);
		return (error_msg){OUTPUT_FILE_ERROR, __func__, "output file didn't open"};
	}

	char buffer[4096];
	size_t bytes;
	while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
		size_t n = fwrite(buffer, 1, bytes, dst_file);
		if (n != bytes) {
			fclose(src_file);
			fclose(dst_file);
			return (error_msg){OVERFLOW_ERROR, __func__, "write write not correct count of bytes"};
		}
	}

	fclose(src_file);
	fclose(dst_file);
	return (error_msg){SUCCESS, "", ""};
}

Flags recognize_command(char *s, int *n) {
	if (strstr(s, "xor") && strlen(s) == 4 && s[3] >= '2' && s[3] <= '6') {
		*n = s[3] - '0';
		return XOR_F;
	} else if (strstr(s, "mask") && strlen(s) == 4) {
		return MASK_F;
	} else if (strstr(s, "copy") && strlen(s) >= 5 && s[4] >= '1') {
		char tmp[strlen(s)];
		strcopy(s, tmp, 4, strlen(s));
		*n = atoi(tmp);
		return COPY_F;
	} else if (strstr(s, "find")) {
		return FIND_F;
	}
	return UNRECOGNIZED_F;
}

error_msg computeLPSArray(const char *pat, int M, int *lps) {
	if (pat == NULL || lps == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	int j = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[j]) {
			j++;
			lps[i] = j;
			i++;
		} else {
			if (j != 0) {
				j = lps[j - 1];
			} else {
				lps[i] = 0;
				i++;
			}
		}
	}
	return (error_msg){SUCCESS, "", ""};
}

error_msg  KMPSearch(char *substring, FILE *f, int *res) {
	if (f == NULL || substring == NULL) {
		return (error_msg){INCORRECT_ARG_FUNCTION, __func__, "get pointer to null"};
	}
	int M = SizeString(substring);

	int lps[M];

	error_msg error = computeLPSArray(substring, M, lps);
	if (error.type) return error;
	int i = 0;
	int j = 0;
	char c = getc(f);
	while (!feof(f)) {
		//		printf("%c", c);
		if (substring[j] == c) {
			j++;
			i++;
			c = getc(f);
		}
		if (j == M) {
			*res = 1;
			return (error_msg){SUCCESS, "", ""};
		} else if (!feof(f) && substring[j] != c) {
			if (j != 0) {
				j = lps[j - 1];
			} else {
				i = i + 1;
				c = getc(f);
			}
		}
	}
	*res = 0;
	return (error_msg){SUCCESS, "", ""};
}