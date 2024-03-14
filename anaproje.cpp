#include <iostream>
#include <string>
#include <fstream>
#include <cctype> 
#include <locale.h>
#include <thread> 

using namespace std;

string encryptDecrypt(const string& message, const string& harfler, const string& anahtar) {
    string result = "";
    for (size_t i = 0; i < message.length(); ++i) {
        size_t index = harfler.find(tolower(message.at(i)));
        if (index != string::npos) {
            result += (isupper(message.at(i)) ? toupper(anahtar.at(index)) : anahtar.at(index));
        }
        else {
            result += message.at(i); // Harf değilse direkt kopyala
        }
    }
    return result;
}

void berkaydosyaSifrele(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");

    string harfler = "abcçdefgğhıijklmnoöprsştuüvyzABCÇDEFGHIİJKLMNOÖPRSŞTUÜVYZ";
    string anahtar = "müfıvejihpğaodyrubşgzcötsçlnkMÜFIVEJİHPĞAODYRUBŞGZCÖTSÇLNK";

    ifstream dosya(dosyaAdi);
    if (!dosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }

    string icerik((istreambuf_iterator<char>(dosya)), istreambuf_iterator<char>());
    dosya.close();

    string sifreliIcerik = encryptDecrypt(icerik, harfler, anahtar);

    ofstream sifreliDosya("encrypted_" + dosyaAdi); // encrypted dosya adı
    if (!sifreliDosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }
    sifreliDosya << sifreliIcerik; // Şifrelenmiş içeriği dosyaya yazma
    sifreliDosya.close();

    string message = "...";
    int repetitionDuration = 5000;
    cout << "Dosyanız şifreleniyor";
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(repetitionDuration / message.length()));
    }

    cout << "Dosya şifrelendi ve güncellendi." << endl;
}

void berkaydosyaCoz(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");

    string harfler = "abcçdefgğhıijklmnoöprsştuüvyzABCÇDEFGHIİJKLMNOÖPRSŞTUÜVYZ";
    string anahtar = "müfıvejihpğaodyrubşgzcötsçlnkMÜFIVEJİHPĞAODYRUBŞGZCÖTSÇLNK";

    ifstream dosya(dosyaAdi);
    if (!dosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }

    string icerik((istreambuf_iterator<char>(dosya)), istreambuf_iterator<char>());
    dosya.close();

    string cozulmusIcerik = encryptDecrypt(icerik, anahtar, harfler);

    ofstream cozulmusDosya("decrypted_" + dosyaAdi); // decrypted dosya adı
    if (!cozulmusDosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }
    cozulmusDosya << cozulmusIcerik; // Çözülen içeriği dosyaya yazma
    cozulmusDosya.close();

    string message = "...";
    int repetitionDuration = 5000;
    cout << "Şifre çözülüyor";
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(repetitionDuration / message.length()));
    }

    cout << "Dosya çözüldü ve güncellendi." << endl;
}
// Uğur şifreleme ve deşifreleme
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

void ugurencrypt_file(const string& file_name, const string& key) {
    ifstream input_file(file_name);
    if (!input_file) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    string plain_text, line;
    while (getline(input_file, line)) {
        plain_text += line;
        plain_text += '\n';
    }
    input_file.close();

    string encrypted_text = vigenere_encrypt(plain_text, key);

    ofstream output_file("encrypted_" + file_name);
    if (!output_file) {
        cerr << "Sifrelenmis dosya olusturulamadi." << endl;
        return;
    }
    output_file << encrypted_text;
    output_file.close();

    string message = "...";
    int repetitionDuration = 5000;
    cout << "Dosya şifreleniyor";
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(repetitionDuration / message.length()));
    }

    cout << "Dosya basariyla sifrelendi: encrypted_" << file_name << endl;
}

void ugurdecrypt_file(const string& file_name, const string& key) {
    ifstream input_file(file_name);
    if (!input_file) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    string encrypted_text, line;
    while (getline(input_file, line)) {
        encrypted_text += line;
        encrypted_text += '\n';
    }
    input_file.close();

    string decrypted_text = vigenere_decrypt(encrypted_text, key);

    ofstream output_file("decrypted_" + file_name);
    if (!output_file) {
        cerr << "Cozulmus dosya olusturulamadi." << endl;
        return;
    }
    output_file << decrypted_text;
    output_file.close();

    string message = "...";
    int repetitionDuration = 5000;
    cout << "Dosya çözülüyor";
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(repetitionDuration / message.length()));
    }

    cout << "Dosya basariyla cozuldu: decrypted_" << file_name << endl;
}
int main()
{
    setlocale(LC_ALL, "Turkish");
    int secenek, secenek2;
    string dosya_adi, cevap, key;
    bool kontrol = true;

    while (kontrol == true)
    {
        cout << "Lütfen şifrelemek ya da şifre çözmek istediğiniz dosyanın adını yazınız:" << endl;
        cin >> dosya_adi;

        cout << "Ceaser Şifrelemesi için 1'e" << endl;
        cout << "Monoalfabetik Şifrelemesi için 2'ye" << endl;
        cout << "Yerine Koyma Şifrelemesi için 3'e basınız.." << endl;
        // Daha fazla gelebilir.
        cin >> secenek;

        cout << "Şifrelemek için 1'e" << endl;
        cout << "Şifre çözmek için 2'ye basınız.." << endl;
        cin >> secenek2;

        switch (secenek2) {
        case 1:
            switch (secenek) {
            case 1:
                break;
            case 2: cout << "Lutfen kullanmak istediginiz anahtari girin: " << endl;
                cin.ignore(); // Önceki cin'in new line karakterini temizle
                getline(cin, key);
                ugurencrypt_file(dosya_adi, key);
                break;
            case 3: berkaydosyaSifrele(dosya_adi);
                break;
            case 4:
                break;
            default:
                cout << "Lütfen geçerli bir değer giriniz:";
                break;
            }
            break; // switch (secenek) bloğundan çık
        case 2:
            switch (secenek) {
            case 1:
                break;
            case 2:    cout << "Lutfen kullanmak istediginiz anahtari girin: " << endl;
                cin.ignore(); // Önceki cin'in new line karakterini temizle
                getline(cin, key);
                ugurdecrypt_file("encrypted_" + dosya_adi, key);
                break;
            case 3: berkaydosyaCoz(dosya_adi);
                break;
            case 4:
                break;
            default:
                cout << "Lütfen geçerli bir değer giriniz:";
                break;
            }
            break; // switch (secenek) bloğundan çık
        default:
            cout << "Lütfen geçerli bir değer giriniz:";
            break;
        }

        cout << "Şifrelemek istediğiniz başka dosya var mı? (Cevabınız 'Evet' ise 'e' veya 'E', 'Hayır' ise 'h' veya 'H' tuşuna basınız): ";
        cin >> cevap;

        if (cevap == "h" || cevap == "H")
            kontrol = false;
    }

    return 0;
}

