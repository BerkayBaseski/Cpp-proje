//Caesar sifreleme
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
// İntegral fonksiyonu girilen a,b,c,sbt,key degerlerine göre olusturulur.
int integral(int x,int y,int z, int d,int k) //fonksiyondaki degerler sırasıyla x=a,y=b,z=c,sbt=d,k=key
{
  int integralSabiti=d;  
  int fx=(x*(pow(k,3)/3))+(y*(pow(k,2)/2))+(z*k)+integralSabiti;
  return fx;
}
int turev(int x,int y,int k)
{
  return 2*x*k+y;
}
string caesarSifreleme(string mesaj, int anahtar)
{
    string sonuc = "";  //Boş bir dizi olan “sonuc“ tanımlandı ve dizi, şifrelenmiş metini biriktirmek için kullanıldı.
    for (int i = 0; i < mesaj.length(); i++) 
    {
        if (isupper(mesaj[i])) //Her karakterin büyük harf mi yoksa küçük harf mi olduğunu kontrol etmek için “ispper” işlevi kullanıldı.
        {
            sonuc += char(int(mesaj[i] + anahtar - 65) % 26 + 65);  
            /*ASCII değeri üzerine anahtar eklenir, ardından 97 çıkarılır (bu, küçük harf karakterlerinin 
            a’dan başladığı konumu temsil eder), sonrasında 26 ile modülenir ve sonuç tekrar 65 eklenerek asıl buyuk harf   karakterine dönüştürülür.*/
        }
        else 
        {
            sonuc += char(int(mesaj[i] + anahtar - 97) % 26 + 97);
        }
    }
    return sonuc;
}
string caesarDeSifreleme(string mesaj, int anahtar)
{
    string sonuc = "";  //Boş bir dize olan “sonuc“ tanımlandı ve dize, şifrelenmiş metini biriktirmek için kullanıldı.
    for (int i = 0; i < mesaj.length(); i++) 
    {
        if (isupper(mesaj[i])) //Her karakterin büyük harf mi yoksa küçük harf mi olduğunu kontrol etmek için “ispper” işlevi kullanıldı.
        {
            sonuc += char(int(mesaj[i]  - anahtar - 65) % 26 + 65);  
            /*ASCII değeri üzerine anahtar çıkarılır, ardından 97 çıkarılır (bu, küçük harf karakterlerinin 
            a’dan başladığı konumu temsil eder), sonrasında 26 ile modülenir ve sonuç tekrar 65 eklenerek asıl buyuk harf karakterine dönüştürülür.*/
        }
        else 
        {
            sonuc += char(int(mesaj[i] - anahtar - 97) % 26 + 97);
        }
    }
    return sonuc;
}
void sifreleme()
{
    int a,b,c,key,sbt; // sbt integral alma islemini gerceklestirebilmemiz icin gerekli  deger
    string metin,sifrelenmisMetin,deSifrelenmisMetin;
    cout<<"ax^2+bx+c seklindeki 2. dereceden denklemin a,b,c degerlerini istediginiz gibi giriniz.\n";
    cout<<"a:";
    cin>>a;
    cout<<"b:";
    cin>>b;
    cout<<"c:";
    cin>>c;
    cout<<"Anahtar gir:";
    cin>>key;
    cout<<"Sifrelemek istediginiz metini giriniz:";
    cin>>metin;
    sbt=a+b+c; //integral sabitini kullanıcının girdigi a+b+c degerlerinin toplamı olarak atandı
    int anahtar=integral(a,b,c,sbt,key)-turev(a,b,key); //anahtar integral ve türev değerlerinin farkına esit
    cout<<"\nSifrelenmis metin:"<<caesarSifreleme(metin,anahtar);
}
void deSifreleme()
{
    int a,b,c,key,sbt; // sbt integral alma islemini gerceklestirebilmemiz icin gerekli  deger
    string metin,sifrelenmisMetin,deSifrelenmisMetin;
    cout<<"ax^2+bx+c seklindeki 2. dereceden denklemin a,b,c degerlerini istediginiz gibi giriniz.\n";
    cout<<"a:";
    cin>>a;
    cout<<"b:";
    cin>>b;
    cout<<"c:";
    cin>>c;
    cout<<"Anahtar gir:";
    cin>>key;
    cout<<"DeSifrelemek istediginiz metini giriniz:";
    cin>>metin;
    sbt=a+b+c; //integral sabitini kullanıcının girdigi a+b+c degerlerinin toplamı olarak atandı
    int anahtar=integral(a,b,c,sbt,key)-turev(a,b,key); //anahtar integral ve türev değerlerinin farkına esit
    cout<<"\nDeSifrelenmis metin:"<<caesarDeSifreleme(metin,anahtar);
}
int main()
{
    int secim1; // kullanıcıdan sifreleme veya deşifreleme yapması için alınır
    cout<<"Sifrelemek icin (1) Desifrelemek icin (2) girin:";
    cin>>secim1;
    if(secim1==1)
    sifreleme();
    else if(secim1==2)
    deSifreleme();
    else
    cout<<"!!!Yanlis giris yaptiniz 1 veya 2 degerini girmelisiniz.PROGRAM SONLANDI!!!";
    return 0;
}