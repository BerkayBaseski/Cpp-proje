#include <iostream>
#include <string>
#include <locale.h>
#include <thread> 

using namespace std;

string encrypt(const string& input, const string& alphabet, const string& key) {
    string result = input;

    for (size_t i = 0; i < input.length(); ++i) {
        size_t index = alphabet.find(tolower(input.at(i)));
        if (index != string::npos) {
            result.at(i) = isupper(input.at(i)) ? toupper(key.at(index)) : key.at(index);
        }
    }

    return result;
}

string decrypt(const string& input, const string& alphabet, const string& key) {
    string result = input;

    for (size_t i = 0; i < input.length(); ++i) {
        size_t index = key.find(tolower(input.at(i)));
        if (index != string::npos) {
            result.at(i) = isupper(input.at(i)) ? toupper(alphabet.at(index)) : alphabet.at(index);
        }
    }

    return result;
}

void printWithDelay(const string& message, int repetitionDuration) {
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(repetitionDuration / message.length()));
    }
}

int main() {
    setlocale(LC_ALL, "Turkish");

    string mesaj;
    string harfler = "abcçdefgğhıijklmnoöprsştuüvyzABCÇDEFGHIİJKLMNOÖPRSŞTUÜVYZ";
    string anahtar = "müfıvejihpğaodyrubşgzcötsçlnkMÜFIVEJİHPĞAODYRUBŞGZCÖTSÇLNK";

    cout << "Şifrelenecek kelimeyi giriniz: ";
    getline(cin, mesaj);

    // Şifreleme
    string encryptedMessage = encrypt(mesaj, harfler, anahtar);
    cout << "Mesaj Şifreleniyor";
    printWithDelay("...\n", 5000);
    cout << "Şifrelenmiş Mesaj: " << encryptedMessage << endl;

    // Çözme
    string decryptedMessage = decrypt(encryptedMessage, harfler, anahtar);
    cout << "Şifre Çözülüyor";
    printWithDelay("...\n", 5000);
    cout << "Çözülen Şifre: " << decryptedMessage << endl;

    return 0;
}
