#include <iostream>
#include <string>
#include <cctype> 
#include <locale.h>
#include <thread> 

using namespace std;
//Fonksiyonlar

int main()
{
    int secenek, secenek2;
    string dosya_adi;

    cout << "Lütfen şifrelemek ya da şifre çözmek istediğiniz dosyanın adını yazınız:" << endl;
    cin >> dosya_adi;

    cout << "Ceaser algoritması için 1'e" <<endl;
    cout << "Monoalfabetik Şifreleme için 2'ye" <<endl;
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
            case 3:
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
        case 3:
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

