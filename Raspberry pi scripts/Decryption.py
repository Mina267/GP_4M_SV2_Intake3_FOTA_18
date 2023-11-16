from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes


def decrypt_file(key, input_file, output_file):
    chunk_size = 64 * 1024

    with open(input_file, 'rb') as file_in, open(output_file, 'wb') as file_out:
        iv = file_in.read(16)
        cipher = AES.new(key, AES.MODE_CBC, iv)

        while True:
            chunk = file_in.read(chunk_size)
            if len(chunk) == 0:
                break
            file_out.write(cipher.decrypt(chunk))

# Usage example
key = b'464F544150524F4A4543544D4B52484F'  # 256-bit key
encrypted_file = 'update.txt.enc'
decrypted_file = 'update.txt'

decrypt_file(key, encrypted_file, decrypted_file)