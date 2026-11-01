#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class uye;
class Kitap;

class Kutuphane
{
public:
    vector<Kitap> kitaplar;
    vector<uye> uyeler;
    string kitap_icin_dosya_adi;
    string uye_icin_dosya_adi;
    vector<pair<string, string>> kullaniciBilgileri;

    bool dogrulama();

    Kutuphane() {}

    void set_dosya_adlari(string kitap_icin_dosya_adi, string uye_icin_dosya_adi)
    {

        this->kitap_icin_dosya_adi = kitap_icin_dosya_adi;
        this->uye_icin_dosya_adi = uye_icin_dosya_adi;
    }

    void envOku();

    void kitapEkle();
    void kitapAra();
    void kitaplariListele();
    void kitapSil();

    void uyeEkle(const uye &uye);
    void uyelerisirala();
    void uyeSil(const string &id);
    void uyeleriKaydet();
    void uyeleriOku();
};

class uye: public Kutuphane
{
public:
    string ad;
    string id;

    uye(string ad, string id) : ad(ad), id(id) {}

    void yazdir() const
    {
        cout << "Ad: " << ad << ", ID: " << id << endl;
    }
};

class personel 
{
};

class Kitap : public Kutuphane
{
public:
    string kitapAdi;
    string yazarAdi;
    string yayinTarihi;

    Kitap(string kitapAdi, string yazarAdi, string yayinTarihi)
        : kitapAdi(kitapAdi), yazarAdi(yazarAdi), yayinTarihi(yayinTarihi) {}
};



string kullaniciAdi;
string parola;

bool Kutuphane::dogrulama()
{
    string kullanici, sifre;
    cout << endl
         << "Kullanici Adi: ";
    cin >> kullanici;
    cout << "Parola: ";
    cin >> sifre;
    cout << endl;
    for (size_t i = 0; i < kullaniciBilgileri.size(); ++i)
    {
        if (kullaniciBilgileri[i].first == kullanici && kullaniciBilgileri[i].second == sifre)
        {
            return true;
        }
    }
    return false;
}

void Kutuphane::envOku()
{
    ifstream envDosyasi("data/kullanicilar.txt");
    if (envDosyasi.is_open())
    {
        string satir;
        string kullaniciAdi, parola;
        while (getline(envDosyasi, satir))
        {
            if (satir.find("KULLANICI_ADI=") != string::npos)
            {
                kullaniciAdi = satir.substr(satir.find("=") + 1);
            }
            else if (satir.find("PAROLA=") != string::npos)
            {
                parola = satir.substr(satir.find("=") + 1);
                kullaniciBilgileri.push_back(make_pair(kullaniciAdi, parola));
            }
        }
        envDosyasi.close();
    }
    else
    {
        cout << "kullanicilar.txt dosyasi acilamadi!" << endl;
    }
}

void Kutuphane::kitapEkle()
{
    fstream dosya;
    dosya.open(kitap_icin_dosya_adi, ios::app);

    if (dosya.is_open())
    {
        string kitapAdi, yazarAdi, yayinTarihi;
        cout << endl
             << "-----------------------------------------------------" << endl;
        cout << "Kitap Adi....: ";
        cin >> ws; // beyaz boşluk karakterını yok sayar
        getline(cin, kitapAdi);
        cout << "Yazar Adi....: ";
        getline(cin, yazarAdi);
        cout << "Yayin Tarihi.: ";
        getline(cin, yayinTarihi);
        cout << endl
             << "--------------------Kitap Eklendi--------------------" << endl;

        dosya << "KITAP_ADI=" << kitapAdi << endl;
        dosya << "YAZAR_ADI=" << yazarAdi << endl;
        dosya << "YAYIN_TARIHI=" << yayinTarihi << endl;

        kitaplar.push_back(Kitap(kitapAdi, yazarAdi, yayinTarihi));
    }
    else
    {
        cout << "Dosya Acilamadi! ";
    }

    dosya.close();
}

void Kutuphane::kitapAra()
{
    string kitapAdi;
    cout << endl
         << "Aranacak kitap adini girin : ";
    cin >> ws;
    getline(cin, kitapAdi);

    fstream dosyaOku(kitap_icin_dosya_adi, ios::in);

    string okunanKitapAdi, okunanYazarAdi, okunanYayinTarihi;
    bool bulundu = false;

    if (dosyaOku.is_open())
    {
        string satir;
        while (getline(dosyaOku, satir))
        {
            if (satir.substr(0, 10) == "KITAP_ADI=")
            {
                okunanKitapAdi = satir.substr(10);
                getline(dosyaOku, satir);
                okunanYazarAdi = satir.substr(10);
                getline(dosyaOku, satir);
                okunanYayinTarihi = satir.substr(13);

                if (okunanKitapAdi == kitapAdi)
                {

                    cout << "------------------------------------ARANAN KITAP BULUNDU--------------------------------------------------" << endl;
                    cout << "Kitap Adi : " << okunanKitapAdi << endl;
                    cout << "Yazar Adi : " << okunanYazarAdi << endl;
                    cout << "Yayin Tarihi : " << okunanYayinTarihi;
                    cout << endl;
                    cout << "--------------------------------------------------------------------------------------------------" << endl;
                    bulundu = true;
                    break;
                }
            }
        }

        if (!bulundu)
        {
            cout << endl
                 << "Aranan kitap bulunamadi" << endl
                 << endl;
        }
    }
    else
    {
        cout << "Dosya Acilamadi!";
    }

    dosyaOku.close();
}

void Kutuphane::kitaplariListele()
{
    fstream dosyaListele;
    dosyaListele.open(kitap_icin_dosya_adi, ios::in);

    if (dosyaListele.is_open())
    {
        string satir;
        string kitapAdi, yazarAdi, yayinTarihi;
        cout << endl
             << "------------------------------KITAPLAR LISTELENDI--------------------------------------------------------" << endl;
        while (getline(dosyaListele, satir))
        {
            if (satir.substr(0, 10) == "KITAP_ADI=")
            {
                kitapAdi = satir.substr(10);
                getline(dosyaListele, satir);
                yazarAdi = satir.substr(10);
                getline(dosyaListele, satir);
                yayinTarihi = satir.substr(13);

                cout << "Kitap Adi : " << kitapAdi << endl;
                cout << "Yazar Adi : " << yazarAdi << endl;
                cout << "Yayin Tarihi : " << yayinTarihi << endl;
                cout << endl;
            }
        }
        cout << "--------------------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "Dosya Acilamadi! ";
    }

    dosyaListele.close();
}

void Kutuphane::kitapSil()
{
    string silinecekKitapAdi;
    cout << endl
         << "Silinecek kitap adini girin : ";
    cin >> ws;
    getline(cin, silinecekKitapAdi);

    fstream dosyaOku(kitap_icin_dosya_adi, ios::in);
    vector<string> kitaplar;

    string satir;
    string okunanKitapAdi, okunanYazarAdi, okunanYayinTarihi;
    bool bulundu = false;

    if (dosyaOku.is_open())
    {
        while (getline(dosyaOku, satir))
        {
            if (satir.substr(0, 10) == "KITAP_ADI=")
            {
                okunanKitapAdi = satir.substr(10);
                getline(dosyaOku, satir);
                okunanYazarAdi = satir.substr(10);
                getline(dosyaOku, satir);
                okunanYayinTarihi = satir.substr(13);

                if (okunanKitapAdi == silinecekKitapAdi)
                {
                    bulundu = true;
                    cout << "---------------------Kitap silindi:------------------ " << okunanKitapAdi << endl;
                }
                else
                {
                    kitaplar.push_back("KITAP_ADI=" + okunanKitapAdi);
                    kitaplar.push_back("YAZAR_ADI=" + okunanYazarAdi);
                    kitaplar.push_back("YAYIN_TARIHI=" + okunanYayinTarihi);
                }
            }
        }

        dosyaOku.close();

        if (!bulundu)
        {
            cout << endl
                 << "Silinmek istenen kitap bulunamadi" << endl
                 << endl;
        }

        fstream dosyaYaz(kitap_icin_dosya_adi, ios::out | ios::trunc);
        if (dosyaYaz.is_open())
        {
            for (size_t i = 0; i < kitaplar.size(); ++i)
            {
                dosyaYaz << kitaplar[i] << endl;
            }
            dosyaYaz.close();
        }
        else
        {
            cout << "Dosya yazilamadi!" << endl;
        }
    }
    else
    {
        cout << "Dosya Acilamadi!";
    }
}

void Kutuphane::uyeEkle(const uye &uye)
{
    for (const auto &u : uyeler)
    {
        if (u.id == uye.id)
        {
            cout << endl
                 << "Bu ID ile zaten bir uye var." << endl;
            return;
        }
    }
    uyeler.push_back(uye);
}

void Kutuphane::uyeleriKaydet()
{
    fstream dosya(uye_icin_dosya_adi, ios::out | ios::trunc);
    if (dosya.is_open())
    {
        for (const auto &u : uyeler)
        {
            dosya << "AD=" << u.ad << endl;
            dosya << "ID=" << u.id << endl;
        }
        dosya.close();
    }
    else
    {
        cout << "Dosya acilamadi!" << endl;
    }
}

void Kutuphane::uyeleriOku()
{
    fstream dosyaOku(uye_icin_dosya_adi, ios::in);

    if (dosyaOku.is_open())
    {
        string satir;
        string ad, id;
        while (getline(dosyaOku, satir))
        {
            if (satir.substr(0, 3) == "AD=")
            {
                ad = satir.substr(3);
                getline(dosyaOku, satir);
                id = satir.substr(3);
                uye yeniUye(ad, id);
                uyeler.push_back(yeniUye);
            }
        }
        dosyaOku.close();
    }
    else
    {
        cout << "Uyeler dosyasi acilamadi!" << endl;
    }
}

void Kutuphane::uyelerisirala()
{
    sort(uyeler.begin(), uyeler.end(), [](const uye &a, const uye &b)
         { return a.ad < b.ad; });

    cout << "-----------------------------------------------------" << endl;
    cout << "Uyeler:" << endl;
    for (const auto &u : uyeler)
    {
        u.yazdir();
    }
    cout << "-----------------------------------------------------" << endl;
}

void Kutuphane::uyeSil(const string &id)
{
    auto it = remove_if(uyeler.begin(), uyeler.end(), [&id](const uye &u)
                        { return u.id == id; });
    if (it != uyeler.end())
    {
        uyeler.erase(it, uyeler.end());
        cout << "-------------------Uye silindi---------------------- " << endl;
    }
    else
    {
        cout << "Bu ID ile bir uye bulunamadÄ±." << endl;
    }
}

using namespace std;

int main()
{
    Kutuphane kutuphanegirisdogrulama;
    kutuphanegirisdogrulama.envOku();

    while (true)
    {
        if (!kutuphanegirisdogrulama.dogrulama())
        {
            cout << "Hatali kullanici adi veya parola. Tekrar deneyiniz." << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << endl
             << "1-Kutuphane Sec \n"
             << "2-Kutuphane Ekle\n"
             << "3-Kutuphane Sil\n"
             << "4-Cikis yap\n "
             << "Seciminiz: " << endl;

        int buton;
        cin >> buton;

        switch (buton)
        {
        case 1:
        {

            Kutuphane kutuphane_A;
            Kutuphane kutuphane_B;

            kutuphane_A.set_dosya_adlari("data/A_kutuphanesi_kitapligi.txt", "data/A_kutuphanesi_uyeleri.txt");
            kutuphane_B.set_dosya_adlari("data/B_kutuphanesi_kitapligi.txt", "data/B_kutuphanesi_uyeleri.txt");

            vector<Kutuphane> kutuphaneler = {kutuphane_A, kutuphane_B};

            int kutuphane_secim;

            while (true)
            {
                cout << endl;
                cout << "Kutuphane ile ilgili islemler icin bir kutuphane secin." << endl;
                cout << "1) A KUTUPHANESI " << endl;
                cout << "2) B KUTUPHANESI " << endl;

                cout << "Seciminiz: " << endl;
                cin >> kutuphane_secim;

                if (kutuphane_secim >= 1 && kutuphane_secim <= 2)
                {
                    break;
                }
                else
                {
                    cout << "Gecersiz secim yaptiniz. Lutfen tekrar deneyiniz" << endl;
                }
            }

            Kutuphane &secilenKutuphane = kutuphaneler[kutuphane_secim - 1];

            secilenKutuphane.uyeleriOku();

            int secim;

            while (true)
            {
                cout << endl
                     << "1-Kitap Ekle \n"
                     << "2-Kitap Ara \n"
                     << "3-Kitaplari Listele \n"
                     << "4-Kitap Sil \n"
                     << "5-Uye Ekle \n"
                     << "6-Uyeleri Listele \n"
                     << "7-Uye Sil \n"
                     << "8-Cikis \n"
                     << "Seciminiz: ";
                cin >> secim;

                if (!(secim))
                {
                    cout << "Gecersiz giris. Lutfen bir sayi girin." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (secim)
                {
                case 1:
                    secilenKutuphane.kitapEkle();
                    break;
                case 2:
                    secilenKutuphane.kitapAra();
                    break;
                case 3:
                    secilenKutuphane.kitaplariListele();
                    break;
                case 4:
                    secilenKutuphane.kitapSil();
                    break;
                case 5:
                {
                    int uyesecim;
                    cout << "Lutfen uye tipini seciniz." << endl;
                    cout << "1) Personel" << endl;
                    cout << "2) Ogrenci" << endl;
                    cin >> uyesecim;
                    switch (uyesecim)
                    {

                    case 1:
                    {
                        string ad, id;
                        cout << endl
                             << "Personel Adi: ";
                        cin >> ws;
                        getline(cin, ad);
                        cout << "Personel ID: ";
                        getline(cin, id);
                        secilenKutuphane.uyeEkle(uye(ad, id));
                        secilenKutuphane.uyeleriKaydet();
                        cout << "--------------------Personel Eklendi------------------";

                        break;
                    }

                    case 2:
                    {
                        string ad, id;
                        cout << endl
                             << "Ogrenci Adi: ";
                        cin >> ws;
                        getline(cin, ad);
                        cout << "Ogrenci ID: ";
                        getline(cin, id);
                        secilenKutuphane.uyeEkle(uye(ad, id));
                        secilenKutuphane.uyeleriKaydet();
                        cout << "--------------------Ogrenci Eklendi------------------";
                        break;
                    }

                    default:
                        break;
                    }
                    break;
                }
                case 6:
                    secilenKutuphane.uyelerisirala();
                    break;
                case 7:
                {
                    string id;
                    cout << endl
                         << "Silinecek Uye ID: ";
                    cin >> ws;
                    getline(cin, id);
                    secilenKutuphane.uyeSil(id);
                    secilenKutuphane.uyeleriKaydet();
                    break;
                }
                case 8:
                    break;
                default:
                    cout << "Gecersiz seÃ§im." << endl;
                }

                if (secim == 8)
                {
                    break; // icteki donguden cik
                }
            }
        }
        break;

        case 2:
        {
            string dosyaAdi;
            cout << "Kutuphane dosyasinin adini girin. (ornegin, data/kutuphane.txt): ";
            cin >> dosyaAdi;

            ofstream yeniDosya(dosyaAdi);
            if (yeniDosya.is_open())
            {
                cout << "Kutuphaneniz olusturuldu." << endl;
            }
            else
            {
                cout << "Kutuphaneniz olusturulamadÄ±." << endl;
            }
        }

        break;

        case 3:
        {
            string dosyaAdi;
            cout << "Silmek istediginiz kutuphane dosyasinin adini girin (ornegin, data/kutuphane.txt): ";
            cin >> ws;
            getline(cin, dosyaAdi);

            if (remove(dosyaAdi.c_str()) != 0)
            {
                cout << "dosyasniz silinemedi";
            }
            else
            {
                cout << "Kutuphane dosyaniz basariyla silindi." << endl;
            }
        }
        break;

        case 4:
            while (true)
            {
                if (!kutuphanegirisdogrulama.dogrulama())
                {
                    cout << "Hatali kullanici adi veya parola. Tekrar deneyiniz." << endl;
                    continue;
                }
                break; // giris dogru olursa dÃ¶ngÃ¼dn cÄ±k
            }
            break;

        default:
            cout << "Gecersiz secim." << endl;
            break;
        }
    }

    return 0;
}