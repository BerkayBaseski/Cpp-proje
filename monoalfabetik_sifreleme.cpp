#include <iostream>
#include <string>
#include <cctype> 
using namespace std;

string encrypt(string plaintext, string key) {
    string ciphertext = "";
    int key_length = key.length();
    
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int offset = c - base;
            char encrypted_char = (key[offset % key_length] - 'A' + c - base) % 26 + base;
            ciphertext += encrypted_char;
        } else {
            ciphertext += c; // Alfabetik olmayan karakterler degismeden kalir
        }
    }
    
    return ciphertext;
}

string decrypt(string ciphertext, string key) {
    string plaintext = "";
    int key_length = key.length();
    
    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int offset = c - base;
            char decrypted_char = (c - base - (toupper(key[i % key_length]) - 'A') + 26) % 26 + base;
            plaintext += decrypted_char;
        } else {
            plaintext += c; // Alfabetik olmayan karakterler degismeden kalir
        }
    }
    
    return plaintext;
}

int main() {
    string plaintext, key;
    cout << "Sifrelenecek metni giriniz:";
    getline(cin, plaintext);
    cout << "Anahtari giriniz:";
    getline(cin, key);
    
    string ciphertext = encrypt(plaintext, key);
    cout << "Sifrelenmis metin: " << ciphertext << endl;
    
    string decrypted_text = decrypt(ciphertext, key);
    cout << "Sifresi cozulmus metin: " << decrypted_text << endl;
    
    return 0;
}

