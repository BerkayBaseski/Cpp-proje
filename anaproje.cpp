#include <iostream>
#include <string>
#include <fstream>
#include <cctype> 
#include <locale.h>
#include <thread> 

using namespace std;
//Berkay Dosya Şifreleme ve Çözme
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

    ofstream sifreliDosya(dosyaAdi); // Aynı dosyayı yazma modunda açma
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

    ofstream cozulmusDosya(dosyaAdi); // Aynı dosyayı yazma modunda açma
    if (!cozulmusDosya) {
        cerr << "Dosya açılamadı." << endl;
        return;
    }
    cozulmusDosya << cozulmusIcerik; // Çözülen içeriği dosyaya yazma
    cozulmusDosya.close();

    string message = "...";
    int repetitionDuration = 5000;
    cout << "Şifre çözülüyor" << endl;
    for (size_t i = 0; i < message.length(); ++i) {
        cout << message[i];
        this_thread::sleep_for(chrono::milliseconds(repetitionDuration / message.length()));
    }

    cout << "Dosya çözüldü ve güncellendi." << endl;
}
//Metehan dosya şifreleme ve çözme

//Uğur dosya şifreleme ve çözme
int main()
{
    int secenek, secenek2;
    string dosya_adi,cevap;
    bool kontrol = true;

    while (kontrol == true)
    {
        cout << "Lütfen şifrelemek ya da şifre çözmek istediğiniz dosyanın adını yazınız:" << endl;
        cin >> dosya_adi;

        cout << "Ceaser algoritması için 1'e" << endl;
        cout << "Monoalfabetik Şifreleme için 2'ye" << endl;
        cout << "Yerine koyma algoritması için 3'e" << endl;
        cout << "";
        // Daha fazla gelebilir.
        cin >> secenek;

        cout << "Şifreleme için 1'e" << endl;
        cout << "Şifre çözmek için 2'ye basınız.." << endl;
        cin >> secenek2;

        switch (secenek2) {
        case 1:
            switch (secenek) {
            case 1:
                break;
            case 2:
                break;
            case 3: berkaydosyaSifrele(dosya_adi);
                break;
            case 4:
                break;
            default:
                cout << "Lütfen geçerli bir değer giriniz:";
                break;
            }
        case 2:
            switch (secenek) {
            case 1:
                break;
            case 2:
                break;
            case 3: berkaydosyaCoz(dosya_adi);
                break;
            case 4:
                break;
            default:
                cout << "Lütfen geçerli bir değer giriniz:";
                break;
            }
        default:
            cout << "Lütfen geçerli bir değer giriniz:";
            break;
        }
    }
    cout << "Şifrelemek istediğiniz başka dosya var mı? (Cevabınız 'Evet' ise 'e' veya 'E', 'Hayır' ise 'h' veya 'H' tuşuna basınız)";
    cin >> cevap;

    if (cevap == "h" || cevap == "H")
        kontrol = false;
}

