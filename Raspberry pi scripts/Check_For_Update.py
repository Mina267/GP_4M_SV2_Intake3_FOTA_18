from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from urllib.request import urlretrieve
import os 

urlretrieve('https://firebasestorage.googleapis.com/v0/b/fota-project-df38a.appspot.com/o/files%2Fupdate.txt.enc?alt=media&token=ba176956-351d-4703-b8c6-09b4192e81c5', 'update.txt.enc')

# Decryption Function
def decrypt_file(key, input_file, output_file):
    chunk_size = 64 * 1024

    with open(input_file, 'rb') as file_in, open(output_file, 'wb') as file_out:
        iv = file_in.read(16)                     # Read the IV from the beginning of the encrypted file
        cipher = AES.new(key, AES.MODE_CBC, iv)   # Create an AES cipher in CBC (Cipher Block Chaining) mode with the provided key and IV

        while True:
            chunk = file_in.read(chunk_size)      # Read a chunk of encrypted data from the input file
            if len(chunk) == 0:
                break
            file_out.write(cipher.decrypt(chunk)) # Decrypt the chunk and write it to the output file


# Parameters will pass to Decryption function for Decryption process            
key = b'464F544150524F4A4543544D4B52484F'  # 32 in hex == 16 byte == 128-bit key
encrypted_file = 'update.txt.enc'
decrypted_file = 'update.txt'

# Call Decryption function for Decryption process
decrypt_file(key, encrypted_file, decrypted_file)

# Open and Store Update file in List line by line
lines = open('update.txt')
lines = [line.rstrip() for line in lines]

# Check (Check.txt) file if exist which mean there is update not installed yet 
# If not Check for Version
check_path = 'Check.txt'
# Check for Version
file_path = 'Version.txt'
if os.path.exists(file_path):
    # If (Version.txt) file exist get stored version and compare with the new one
    file = open('Version.txt','r+')
    Version = file.read()
    if lines[0] == Version:
        # In case same version exist
        if os.path.exists(check_path):
            print("New Update avilable")
        else:
            print("No updates are avilable")
    else:
        # If new Version
        print("New Update avilable")
        open("Check.txt",'w')
        file.seek(0)
        Version = lines[0]
        file.write(Version)
else:
    # Case if downloaded update first update
    # Then generate Version.txt file to save which version for check vesion after that 
    # And create Check file which indicate there is an update
    file = open('Version.txt','w')
    Version = lines[0]
    file.write(Version)
    print("New Update avilable")
    open("Check.txt",'w')