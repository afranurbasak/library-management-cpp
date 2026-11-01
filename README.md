# Library Management System (C++)

> 3 kişilik ekip projesi / 3-person team project

## 🇹🇷 Türkçe

### Proje Hakkında
C++ ile nesne yönelimli programlama ilkeleri kullanılarak geliştirilmiş, konsol tabanlı bir kütüphane yönetim sistemidir. Birden fazla kütüphanenin kitap ve üye kayıtları ayrı metin dosyalarında tutulur; kullanıcı girişinden sonra kütüphane seçilerek işlemler yapılır.

### Özellikler
- Dosyadan okunan kullanıcı bilgileriyle giriş
- İki hazır kütüphane (A ve B) arasında seçim; yeni kütüphane dosyası ekleme ve silme
- Kitap ekleme, arama, listeleme ve silme (kitap adı, yazar, yayın yılı)
- Üye ekleme (personel / öğrenci), listeleme ve silme
- Verilerin metin dosyalarında kalıcı olarak saklanması
- Sınıf yapısı: `Kutuphane` temel sınıfından türeyen `Kitap` ve `uye` sınıfları, ayrıca `personel` sınıfı (kalıtım)
- Hatalı giriş ve geçersiz seçim kontrolleri

### Kullanılan Teknolojiler
C++ (C++11 ve üzeri), STL (`vector`, `string`, `algorithm`), `fstream`

### Kurulum
```bash
git clone https://github.com/afranurbasak/library-management-cpp.git
cd library-management-cpp
g++ -std=c++17 main.cpp -o library
```
Windows'ta Visual Studio, Dev-C++ veya MinGW ile de derlenebilir.

### Kullanım
Programı depo kök dizininden çalıştırın; veri dosyaları `data/` klasöründen okunur:
```bash
./library
```
Demo giriş bilgileri: kullanıcı adı `admin`, şifre `1234` (`data/kullanicilar.txt`). Örnek veriler kurgusaldır. Arayüz metinleri Türkçedir.

## 🇬🇧 English

### About the Project
A console-based library management system developed in C++ using object-oriented programming principles. Book and member records for several libraries are kept in separate text files; after logging in, the user selects a library and performs operations on it.

### Features
- Login with user credentials read from a file
- Choosing between two built-in libraries (A and B); adding and deleting library files
- Adding, searching, listing and deleting books (title, author, publication year)
- Adding (staff / student), listing and deleting members
- Persistent storage in text files
- Class design: `Kitap` (book) and `uye` (member) classes derived from the `Kutuphane` (library) base class, plus a `personel` (staff) class (inheritance)
- Input validation and invalid-choice handling

### Technologies
C++ (C++11 or later), STL (`vector`, `string`, `algorithm`), `fstream`

### Installation
```bash
git clone https://github.com/afranurbasak/library-management-cpp.git
cd library-management-cpp
g++ -std=c++17 main.cpp -o library
```
It can also be compiled on Windows with Visual Studio, Dev-C++ or MinGW.

### Usage
Run the program from the repository root; data files are read from `data/`:
```bash
./library
```
Demo login: username `admin`, password `1234` (`data/kullanicilar.txt`). Sample data is fictional. The user interface is in Turkish.
