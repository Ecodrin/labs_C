//
// Created by matvey on 11/18/24.
//

#include "ex2.hpp"

#include <fstream>

void encoder::set(const std::vector<uint8_t>& key) { this->key = key; }

void encoder::encode(const std::string& input_filename, const std::string& output_filename,
                     [[maybe_unused]] const bool is_encryption) {
	if(std::filesystem::equivalent(input_filename, output_filename)){
		throw std::invalid_argument("get one files");
	}
	std::ifstream in;
	in.open(input_filename, std::ios::binary);
	if (!in.is_open()) {
		throw std::invalid_argument("first file didn't open");
	}
	std::ofstream out;
	out.open(output_filename, std::ios::binary);
	if (!out.is_open()) {
		in.close();
		throw std::invalid_argument("second file didn't open");
	}

	std::vector<uint8_t> s_box(256);
	initialize_s_box(s_box, key);
	char buf;
	size_t i = 0;
	size_t j = 0;
	while (in.get(buf)){
		uint8_t key_byte = generate_key_stream(s_box, i, j);
		uint8_t data_byte = buf;
		uint8_t result_byte = data_byte ^ key_byte;
		out.put(static_cast<char>(result_byte));
	}

	in.close();
	out.close();
}


/**
 * https://ru.wikipedia.org/wiki/RC4
 *
 * for i from 0 to 255\n
 * 		S[i] := i\n
 * endfor\n
 * j := 0\n
 * for i from 0 to 255\n
 * 		j := ( j + S[i] + Key[ i mod L ] ) mod 256 // n = 8 ; 28 = 256\n
 * 		поменять местами S[i] и S[j]\n
 * endfor \n
 */

void encoder::initialize_s_box(std::vector<uint8_t>& s_box, const std::vector<uint8_t>& key) {
	for (size_t i = 0; i < 256; ++i) {
		s_box[i] = i;
	}

	size_t j = 0;
	for (size_t i = 0; i < 256; ++i) {
		i = (i + 1) % 256;
		j = (j + s_box[i]) % 256;
		j = (j + s_box[i] + key[i % key.size()]) % 256;
		std::swap(s_box[i], s_box[j]);
	}
}

/**
 * https://ru.wikipedia.org/wiki/RC4
 *
 * i := ( i + 1 ) mod 256
 * j := ( j + S[i] ) mod 256
 * поменять местами S[i] и S[j]
 * t := ( S[i] + S[j] ) mod 256
 * ключ K := S[t]
 */

uint8_t encoder::generate_key_stream(std::vector<uint8_t>& s_box, size_t& i, size_t& j) {
	std::swap(s_box[i], s_box[j]);
	return s_box[(s_box[i] + s_box[j]) % 256];
}
std::vector<uint8_t> encoder::get() const { return key; }
