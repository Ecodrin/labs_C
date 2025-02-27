import os

def calculate_xor(file_path, block_bits):
    with open(file_path, 'rb') as f:
        data = f.read()
    block_size = block_bits // 8
    xor_result = bytearray(block_size)
    for i in range(0, len(data), block_size):
        block = data[i:i+block_size].ljust(block_size, b'\x00')
        for j in range(block_size):
            xor_result[j] ^= block[j]
    return bytes(xor_result)

# Пример для N=3 (8 бит):
result = calculate_xor("random2.bin", 32)
print(f"Ожидаемый XOR_F: {result.hex()}")


