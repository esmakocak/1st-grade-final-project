// Esma KOÇAK, 152120211058

#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <ctime>
using namespace std;

fstream myFile;

// PERSONAL INFORMATION
//Person struct where information about persons will be kept
struct Person 
{
    string id;
    string name;
    string surname;
    int age;
    string city;
    string date = "01.06.2020";
    int dose;
    string vaccine = "NULL";
} p;

string getId(); // GENERATE ID

Person getData(Person p); // REGISTER IN THE SYSTEM

void login(); // LOGIN TO THE SYSTEM

void menu(string usertempid); // MENU

void viewData(string usertempid); // SEE PERSON'S INFORMATIONS

void updateData(string usertempid, Person &p); // SEE PERSON'S INFORMATIONS

void vaccineData(); // register vaccine

int main()
{

    int num;
    cout << "Kayit olmak icin 1'e, uye girisi yapmak icin 2'ye basiniz. " << endl;
    cin >> num;
    if (num == 1)
    {
        cin.ignore();
        getData(p);
    }
    else if (num == 2)
    {
        login();
    }
    return 0;
}

// GENERATE ID
string getId()
{
    //this function creates id with this format--> letter,letter,number,number.

    srand(time(NULL));
    string nums = "0123456789";
    char c;
    int r;
    char letters[2];
    char numx[2];
    char id[5];
    id[4] = '\0';

    for (int i = 0; i < 2; i++) //for döngüsü içinde rand fonksiyonuyla rastgele 2 sayı ve 2 harf üretiliyor.
    {
        r = rand() % 26;
        c = 'A' + r;
        letters[i] = c;
        int temp = rand() % 10;
        char num = nums[temp];
        numx[i] = num;  //harfler bir dizide, sayılar bir dizide tutulduktan sonra bu dizilerin elemanlarıyla id dizisi oluşturuluyor.
        int j = i + 2;
        id[i] = letters[i]; //harf dizisinin ilk iki elemanı id dizisinin ilk iki elemanına, sayı dizisinin elemanları ise sırasıyla id dizisinin 3. ve 4. elemanlarına atanıyor.
        id[j] = numx[i];
    } 

    
    return id;
}

// SİSTEME KAYIT OL
Person getData(Person p)
{
    string tempId = getId(); //call the function which creates random id
    cout << "Adinizi giriniz: ";
    cin >> p.name;
    cout << "Soyadinizi giriniz: ";
    cin >> p.surname;
    cout << "Yasinizi giriniz: ";
    cin >> p.age;
    cout << "Yasadiginiz ili yaziniz: ";
    cin >> p.city;
    p.dose = 0;
    cout << "Yeni kayit olusturuldu: " << p.name << " " << p.surname << " " << p.age << " " << p.city << " " << p.date << " " << p.dose << " " << p.vaccine << " " << endl;
    cout << "Id'niz: " << tempId << endl
         << endl
         << "Id'nizi saklayiniz, daha sonra giris yapmak icin kullanacaksiniz." << endl;
    cout << "Giris yapma sayfasina yonlendiriliyorsunuz..." << endl
         << endl;
    myFile.open("database.txt", ios::app); // append
    if (myFile.is_open()) 
    {   //kullanıcıdan aldığımız bilgileri dosyaya kaydediyoruz:
        myFile << tempId << " " << p.name << " " <<p.surname<< " " << p.age << " " << p.city << " " << p.date << " " << p.dose << " " << p.vaccine << " " << endl;
        myFile.close();
    }
    login(); 

    return p;
}

// GİRİS YAP
void login()
{
    cout << "Id'nizi giriniz:  " << endl;
    string usertempid;
    cin >> usertempid; 
    //kullanıcıdan id'si alınıyor, daha sonra "usertempid" menü fonksiyonuna ve menünün içindeki kayıt görüntüleme/güncelleme fonksiyonlarına da bu id yollanacak ve kullanıcı bilgilerine erişim böylelikle sağlanacak.

    myFile.open("database.txt", ios::in); // open a file to perform read operation using file object
    if (myFile.is_open()) // checking whether the file is open
    {
        string str;
        int temp = 0;
        while (getline(myFile, str)) // read data from file object and put it into string.
        {
            string substr = str.substr(0, 4);

            if (usertempid == substr) 
            //if the current line's first 4 characters are equal to the personal id then it will login
            {
                cout << "Giris basarili " << endl;
                temp = 1;
                myFile.close();
                menu(usertempid);
            }
        }
        if (temp == 0)
        {
            cout << "Id bulunamadi, lütfen tekrar deneyiniz." << endl;
            myFile.close();
            login();
        }
    }
}

// MENU
void menu(string usertempid)
{
    int *operation;
    operation = new int;
    cout << "Menuye girmek icin 1'e, cikis yapmak icin 2'ye basiniz: " << endl;
    cin >> *operation;
    if (*operation == 1)
    {
        while (*operation == 1)
        {
            cout << "---------------" << endl;
            cout << "MENU\n";
            cout << "1-Kayit Goruntule" << endl;
            cout << "2-Kayit Guncelle" << endl;
            cout << "3-Asi Kaydi Yaptir" << endl;
            cout << "---------------" << endl;
            int option;
            cout << "islem seciniz:" << endl;
            cin >> option;
            switch (option)
            {
            case 1:
                viewData(usertempid);
                break;
            case 2:
                updateData(usertempid, p);
                break;
            case 3:
                cout << "asiKaydiYaptir() " << endl;
                break;
            }
            cout << endl
                 << "Menuye donmek icin 1'e, cikis yapmak icin 2'ye basiniz: " << endl;
            cin >> *operation;
            if (*operation == 2)
            {
                cout << "Cikis yapildi." << endl;
            }
        }
    }
    else
    {
        cout << "Cikis yapildi." << endl;
    }
}



// KAYIT GORUNTULE
void viewData(string usertempid)
{
    cout << "KULLANICI BILGILERI" << endl;
    cout << "-------------------" << endl;
    myFile.open("database.txt", ios::in);
    if (myFile.is_open())
    {
        string str;
        while (getline(myFile, str))
        {
            string substr = str.substr(0, 4);
            if (usertempid == substr)
            {
                cout << str << endl;
            }
        }
        myFile.close();
    }
}

// KAYIT GUNCELLE
void updateData(string usertempid, Person &p)
{
    cout << "KULLANICI BILGILERINI GUNCELLEME\n"
         << "--------------------------------\n";
    myFile.open("database.txt", ios::in);
    if (myFile.is_open())
    {
        string str;
        ofstream newFile;
        string str2;
        newFile.open("new.txt");
        while (getline(myFile, str))
        {
            string substr = str.substr(0, 4);
            if (usertempid == substr)
            {
                cout << "Adinizi giriniz: ";
                cin>> p.name;
                cout << "Soyadinizi giriniz: ";
                cin>> p.surname;
                cout << "Yasinizi giriniz: ";
                cin >> p.age;
                cout << "Yasadiginiz ili yaziniz: ";
                cin >> p.city;
                
                newFile << usertempid << " " << p.name << " " << p.surname<< " " <<p.age << " " << p.city << " " << p.date << " " << p.dose << " " << p.vaccine << " " << endl;
            }
            else
            {
                newFile << str << endl;
            }
        }
        myFile.close();
        newFile.close();
        remove("database.txt");
        rename("new.txt", "database.txt");
        cout << "Bilgileriniz guncellendi." << endl;
    }
}

// ASI KAYDI YAPTIR
void vaccineData() {}

