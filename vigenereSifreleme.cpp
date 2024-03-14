#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string vigenere_encrypt(const string& plain_text, const string& key) {
    string encrypted_text = "";
    int key_index = 0;
    for (size_t i = 0; i < plain_text.length(); ++i) {
        char character = plain_text[i];
        if (isalpha(character)) {
            char base = islower(character) ? 'a' : 'A';
            int shift = tolower(key[key_index % key.length()]) - 'a';
            character = static_cast<char>((character - base + shift) % 26 + base);
            key_index++;
        }
        encrypted_text += character;
    }
    return encrypted_text;
}

string vigenere_decrypt(const string& encrypted_text, const string& key) {
    string decrypted_text = "";
    int key_index = 0;
    for (size_t i = 0; i < encrypted_text.length(); ++i) {
        char character = encrypted_text[i];
        if (isalpha(character)) {
            char base = islower(character) ? 'a' : 'A';
            int shift = tolower(key[key_index % key.length()]) - 'a';
            character = static_cast<char>((character - base - shift + 26) % 26 + base);
            key_index++;
        }
        decrypted_text += character;
    }
    return decrypted_text;
}

int main() {
    string plain_text, key;
    
    cout << "Lutfen sifrelemek istediginiz metni girin: ";
    getline(cin, plain_text);
    
    cout << "Lutfen kullanmak istediginiz anahtari girin: ";
    getline(cin, key);

    string encrypted_text = vigenere_encrypt(plain_text, key);
    cout << "Sifrelenmis Metin: " << encrypted_text << endl;

    string decrypted_text = vigenere_decrypt(encrypted_text, key);
    cout << "Cozulmus Metin: " << decrypted_text << endl;

    return 0;
}

