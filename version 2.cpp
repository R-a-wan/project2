#include <iostream>
#include <fstream>
#include <vector>

// Function to encrypt/decrypt the file using Caesar Cipher
void processFile(const std::string& filename, int key) {
    // Open the file in binary mode
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    
    if (!file) {
        std::cerr << "Failed to open the file!" << std::endl;
        return;
    }
    filesystem::path filePath = filename;
 
    if (filePath.extension().c_str()==".png"){
        // Read the PNG signature (first 8 bytes)
         unsigned char pngSignature[8];
         file.read(reinterpret_cast<char*>(pngSignature), 8);
    
         // Check if it's a PNG file (signature should be 89 50 4E 47 0D 0A 1A 0A)
         const unsigned char pngMagic[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
         if (memcmp(pngSignature, pngMagic, 8) != 0) {
             std::cerr << "The file is not a valid PNG file!" << std::endl;
         }

    }
    else if (filePath.extension().c_str()==".pdf"){
        // Read the pdf signature (first 8 bytes)
         unsigned char pdfSignature[8];
         file.read(reinterpret_cast<char*>(pdfSignature), 8);
    
         // Check if it's a Pdf file (signature should be 25 50 44 46 2D 31 2E 35 )
         const unsigned char pdfMagic[8] = {0x25, 0x50, 0x44, 0x46, 0x2D, 0x31, 0x2E, 0x35};
         if (memcmp(pngSignature, pdfgMagic, 8) != 0) {
             std::cerr << "The file is not a valid pdf file!" << std::endl;
         }

    }

    // Read the next byte to check if the file is already encrypted (we'll use this as our custom flag)
    char flag;
    file.read(&flag, 1);
    bool isEncrypted = (flag == 'E'); // 'E' for Encrypted

    // Seek to the beginning of the file content, skipping the PNG signature and flag
    file.seekg(8 + 1, std::ios::beg);

    // Encrypt or decrypt
    char operation;
    if (isEncrypted) {
        // Decrypting
        std::cout << "Decrypting the PNG file..." << std::endl;
        operation = 'D';
    } else {
        // Encrypting, so add an 'E' flag at the 9th byte position
        std::cout << "Encrypting the PNG file..." << std::endl;
        operation = 'E';
        file.seekp(8, std::ios::beg);
        file.put('E');
    }

    // Read the rest of the file content
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Process the content using Caesar Cipher
    for (auto& byte : buffer) {
        byte = (isEncrypted) ? byte - key : byte + key;
    }

    // Seek to the right position to write back
    file.seekp(8 + 1, std::ios::beg);

    // Write the processed content back to the file
    file.write(buffer.data(), buffer.size());

    // Close the file
    file.close();

    std::cout << "Operation completed: " << ((operation == 'E') ? "Encryption" : "Decryption") << std::endl;
}

int main() {
    std::string filename;
    int key;

    std::cout << "Enter the filename (PNG file): ";
    std::cin >> filename;

    std::cout << "Enter the encryption key: ";
    std::cin >> key;

    // Process the file with the provided key
    processFile(filename, key);

    return 0;
}
