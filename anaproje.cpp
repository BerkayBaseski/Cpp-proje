#include <iostream>
#include <string>
#include <fstream>
#include <cctype> 
#include <clocale>
#include <thread> 
#include <math.h>

using namespace std;

string encrypt(const string& input, const string& alphabet, const string& key) {
    string result = input;

    for (size_t i = 0; i < input.length(); ++i) {
        char currentChar = input.at(i);
        char transformedChar = isupper(currentChar) ? tolower(currentChar) : currentChar;
        size_t index = alphabet.find(transformedChar);
        if (index != string::npos) {
            char encryptedChar = isupper(currentChar) ? toupper(key.at(index)) : key.at(index);
            result.at(i) = encryptedChar;
        }
    }

    return result;
}

string decrypt(const string& input, const string& alphabet, const string& key) {
    string result = input;

    for (size_t i = 0; i < input.length(); ++i) {
        char currentChar = input.at(i);
        char transformedChar = isupper(currentChar) ? tolower(currentChar) : currentChar;
        size_t index = key.find(transformedChar);
        if (index != string::npos) {
            char decryptedChar = isupper(currentChar) ? toupper(alphabet.at(index)) : alphabet.at(index);
            result.at(i) = decryptedChar;
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

    string sifreliIcerik = encrypt(icerik, harfler, anahtar);

    ofstream sifreliDosya("sifrelenmis_" + dosyaAdi);
    if (!sifreliDosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }
    sifreliDosya << sifreliIcerik;
    sifreliDosya.close();

    string message = "...";
    int zaman = 5000;
    cout << "Dosyanız şifreleniyor";
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(zaman / message.length()));
    }

    cout << "Dosya şifrelendi ve güncellendi: sifrelenmis_" << dosyaAdi << endl;
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

    string cozulmusIcerik = decrypt(icerik, harfler, anahtar);

    ofstream cozulmusDosya("cozulmus_" + dosyaAdi);
    if (!cozulmusDosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }
    cozulmusDosya << cozulmusIcerik;
    cozulmusDosya.close();

    string message = "...";
    int zaman = 5000;
    cout << "Şifre çözülüyor";
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(zaman / message.length()));
    }

    cout << "Dosya çözüldü ve güncellendi: cozulmus_" << dosyaAdi << endl;
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
        plain_text += line; // newline karakterini ekleme
    }
    input_file.close();

    string encrypted_text = vigenere_encrypt(plain_text, key);

    ofstream output_file("sifrelenmis_" + file_name);
    if (!output_file) {
        cerr << "Sifrelenmis dosya olusturulamadi." << endl;
        return;
    }
    output_file << encrypted_text;
    output_file.close();

    cout << "Dosya basariyla sifrelendi: sifrelenmis_" << file_name << endl;
}

void ugurdecrypt_file(const string& file_name, const string& key) {
    ifstream input_file(file_name);
    if (!input_file) {
        cerr << "Dosya acilamadi." << endl;
        return;
    }

    string encrypted_text, line;
    while (getline(input_file, line)) {
        encrypted_text += line; // newline karakterini ekleme
    }
    input_file.close();

    string decrypted_text = vigenere_decrypt(encrypted_text, key);

    // Orijinal dosya adını oluştur
    string original_file_name = file_name.substr(10); // "sifrelenmis_" öneki çıkarıldı

    ofstream output_file("cozulmus_" + original_file_name); // Orijinal dosya adını kullan
    if (!output_file) {
        cerr << "Cozulmus dosya olusturulamadi." << endl;
        return;
    }
    output_file << decrypted_text;
    output_file.close();

    cout << "Dosya basariyla cozuldu: cozulmus_" << original_file_name << endl;
}

//Metehan dosya şifreleme ve çözme
string metehandosyaIcerigiOku(const string& dosya_adi) {
    ifstream dosya(dosya_adi);
    if (!dosya.is_open()) {
        cerr << "Hata: Dosya açılamadı." << endl;
        return "";
    }

    string icerik;
    string satir;
    while (getline(dosya, satir)) {
        icerik += satir + "\n";
    }

    dosya.close();

    return icerik;
}

int integral(int x, int y, int z, int d, int k) {
    int integralSabiti = d;
    int fx = (x * (pow(k, 3) / 3)) + (y * (pow(k, 2) / 2)) + (z * k) + integralSabiti;
    return fx;
}

int turev(int x, int y, int k) {
    return 2 * x * k + y;
}

string caesarSifreleme(string mesaj, int anahtar) {
    string sonuc = "";
    for (int i = 0; i < mesaj.length(); i++) {
        if (isupper(mesaj[i])) {
            sonuc += char(((mesaj[i] - 'A') + anahtar) % 26 + 'A');
        }
        else if (islower(mesaj[i])) {
            sonuc += char(((mesaj[i] - 'a') + anahtar) % 26 + 'a');
        }
        else {
            sonuc += mesaj[i]; // Harf olmayan karakterler için doğrudan kopyala
        }
    }
    return sonuc;
}

string caesarDeSifreleme(string mesaj, int anahtar) {
    return caesarSifreleme(mesaj, 26 - anahtar); // Deşifreleme, şifreleme ile aynı mantıkla yapılır.
}

void metehansifreleme(const string& dosya_adi) {
    string icerik = metehandosyaIcerigiOku(dosya_adi);

    int a, b, c, key, sbt;
    cout << "ax^2+bx+c şeklindeki 2. dereceden denklemin a, b, c değerlerini istediğiniz gibi giriniz.\n";
    cout << "a:";
    cin >> a;
    cout << "b:";
    cin >> b;
    cout << "c:";
    cin >> c;
    key = 1;
    sbt = a + b + c;
    int anahtar = integral(a, b, c, sbt, key) - turev(a, b, key);

    string sifreliIcerik = caesarSifreleme(icerik, anahtar);

    ofstream sifreliDosya("sifrelenmis_" + dosya_adi);
    if (!sifreliDosya) {
        cerr << "Şifrelenmiş dosya oluşturulamadı." << endl;
        return;
    }
    sifreliDosya << sifreliIcerik;
    sifreliDosya.close();

    cout << "Dosya şifrelendi ve sifrelenmis_" << dosya_adi << " adında kaydedildi." << endl;
}

void metehandeSifreleme(const string& dosya_adi) {
    string icerik = metehandosyaIcerigiOku(dosya_adi);

    int a, b, c, key, sbt;
    cout << "ax^2+bx+c şeklindeki 2. dereceden denklemin a, b, c değerlerini istediğiniz gibi giriniz.\n";
    cout << "a:";
    cin >> a;
    cout << "b:";
    cin >> b;
    cout << "c:";
    cin >> c;
    key = 1;
    sbt = a + b + c;
    int anahtar = integral(a, b, c, sbt, key) - turev(a, b, key);

    string cozulmusIcerik = caesarDeSifreleme(icerik, anahtar);

    ofstream cozulmusDosya("cozulmus_" + dosya_adi);
    if (!cozulmusDosya) {
        cerr << "Çözülmüş dosya oluşturulamadı." << endl;
        return;
    }
    cozulmusDosya << cozulmusIcerik;
    cozulmusDosya.close();

    cout << "Dosya çözüldü ve cozulmus_" << dosya_adi << " adında kaydedildi." << endl;
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

        cout << "Ceaser Sifrelemesi için 1'e" << endl;
        cout << "Monoalfabetik Sifrelemesi için 2'ye" << endl;
        cout << "Yerine Koyma Sifrelemesi için 3'e basınız.." << endl;
        // Daha fazla gelebilir.
        cin >> secenek;

        cout << "Şifrelemek için 1'e" << endl;
        cout << "Şifre çözmek için 2'ye basınız.." << endl;
        cin >> secenek2;

        switch (secenek2) {
        case 1:
            switch (secenek) {
            case 1:metehandosyaIcerigiOku(dosya_adi);
                metehansifreleme(dosya_adi);
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
            case 1:metehandosyaIcerigiOku(dosya_adi);
                metehandeSifreleme(dosya_adi);
                break;
            case 2:    cout << "Lutfen kullanmak istediginiz anahtari girin: " << endl;
                cin.ignore(); // Önceki cin'in new line karakterini temizle
                getline(cin, key);
                ugurdecrypt_file(dosya_adi, key);
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