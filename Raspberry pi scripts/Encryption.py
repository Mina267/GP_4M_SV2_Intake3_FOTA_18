from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

def encrypt_file(key, input_file, output_file):
    chunk_size = 64 * 1024
    iv = get_random_bytes(16)
    cipher = AES.new(key, AES.MODE_CBC, iv)

    with open(input_file, 'rb') as file_in, open(output_file, 'wb') as file_out:
        file_out.write(iv)

        while True:
            chunk = file_in.read(chunk_size)
            if len(chunk) == 0:
                break
            elif len(chunk) % 16 != 0:
                chunk += b' ' * (16 - len(chunk) % 16)  # Padding
            file_out.write(cipher.encrypt(chunk))


# Our Key in ASCII --> FOTAPROJECTMKRHO
key = b'464F544150524F4A4543544D4B52484F'  # 32 in hex == 16 byte == 128-bit key
input_file = 'update.txt'
encrypted_file = 'update.txt.enc'

encrypt_file(key, input_file, encrypted_file)
