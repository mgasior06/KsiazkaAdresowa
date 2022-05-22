#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Kontakt
{
    int id, idUzytkownika;
    string imie, nazwisko, numerTelefonu, adresEmail, adresZamieszkania;
};

struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};

int odczytZPliku (vector<Kontakt> &kontakty, int &id)
{
    int nrPipe = 0;
    int i = 0;
    char pipe = '|';
    string wycietaFraza = "";
    string linia;
    fstream plik;

    plik.open("ksiazka_adresowa.txt", ios::in);
    if(plik.good() == false)
    {
        cout << "Plik ksiazka_adresowa.txt nie istnieje!";
    }
    while(getline(plik,linia))
    {
        kontakty.push_back(Kontakt());
        while(linia!="")
        {
            size_t pozycja = linia.find(pipe);
            wycietaFraza = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            nrPipe++;

            switch(nrPipe)
            {
            case 1:
                kontakty[i].id = atoi(wycietaFraza.c_str());
                //id = kontakty[i].id;
                break;
            case 2:
                kontakty[i].idUzytkownika = atoi(wycietaFraza.c_str());
                break;
            case 3:
                kontakty[i].imie = wycietaFraza;
                break;
            case 4:
                kontakty[i].nazwisko = wycietaFraza;
                break;
            case 5:
                kontakty[i].numerTelefonu = wycietaFraza;
                break;
            case 6:
                kontakty[i].adresEmail = wycietaFraza;
                break;
            case 7:
                kontakty[i].adresZamieszkania = wycietaFraza;
                break;

            }
            wycietaFraza = "";
        }
        id = kontakty[i].id;
        i++;
        nrPipe = 0;
    }
    plik.close();

    return kontakty.size();
}

void zapiszDoPliku (vector<Kontakt> &kontakty, int liczbaKontaktow)
{
    char pipe = '|';
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    plik << kontakty[liczbaKontaktow].id << pipe;
    plik << kontakty[liczbaKontaktow].idUzytkownika << pipe;
    plik << kontakty[liczbaKontaktow].imie << pipe;
    plik << kontakty[liczbaKontaktow].nazwisko << pipe;
    plik << kontakty[liczbaKontaktow].numerTelefonu << pipe;
    plik << kontakty[liczbaKontaktow].adresEmail << pipe;
    plik << kontakty[liczbaKontaktow].adresZamieszkania << pipe << endl;
    plik.close();
}

void powrotDoMenu ()
{
    cout << "Powrot do MENU [enter]" << endl;
    getchar();
}

void wyswietlKontakt (vector<Kontakt> &kontakty, int i)
{
    cout << "ID: " << kontakty[i].id << endl;
    cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
    cout << "Tel. " << kontakty[i].numerTelefonu << endl;
    cout << "e-mail " << kontakty[i].adresEmail << endl;
    cout << "Adres: " << kontakty[i].adresZamieszkania << "\n" <<endl;
}

void komunikatBrakKontaktow ()
{
    cout << "Brak zapisanych kontaktow." << endl;
    cin.ignore();
    powrotDoMenu();
}

void komunikatBrakTakiegoKontaktu ()
{
    cout << "Brak takiego kontaktu." << endl;
    cin.ignore();
    powrotDoMenu();
}

void wyszukajPoImieniu (vector<Kontakt> &kontakty, int liczbaKontaktow)
{
    system("cls");
    string imie;
    char wybor;
    int pomocnicza = 0;
    if (liczbaKontaktow > 0)
    {
        cout << "Wpisz imie: ";
        cin >> imie;
        cout << endl;
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            if (kontakty[i].imie == imie)
            {
                wyswietlKontakt (kontakty, i);
                pomocnicza = pomocnicza + 1;
            }
        }
        if (pomocnicza == 0)
        {
            cout << "Brak kontaktow o tym imieniu." << endl;
        }
        cin.ignore();
        powrotDoMenu();
    }
    else komunikatBrakKontaktow();
}

void wyszukajPoNazwisku (vector<Kontakt> &kontakty, int liczbaKontaktow)
{
    system("cls");
    string nazwisko;
    char wybor;
    int pomocnicza = 0;
    if (liczbaKontaktow > 0)
    {
        cout << "Wpisz nazwisko: ";
        cin >> nazwisko;
        cout << endl;
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            if (kontakty[i].nazwisko == nazwisko)
            {
                wyswietlKontakt (kontakty, i);
                pomocnicza = pomocnicza + 1;
            }
        }
        if (pomocnicza == 0)
        {
            cout << "Brak kontaktow o tym nazwisku." << endl;
        }
        cin.ignore();
        powrotDoMenu();
    }
    else komunikatBrakKontaktow();
}

void wyswietlKontakty (vector<Kontakt> &kontakty, int liczbaKontaktow)
{
    system("cls");
    if (liczbaKontaktow > 0)
    {
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            wyswietlKontakt (kontakty, i);
        }
        cin.ignore();
        powrotDoMenu();
    }
    else komunikatBrakKontaktow();
}

int dodajKontakt (vector<Kontakt> &kontakty, int liczbaKontaktow, int &id, int idUzytkownika)
{
    system("cls");
    char pipe = '|';
    string imie, nazwisko, numerTelefonu, adresEmail, adresZamieszkania;
    cout << "Podaj imie" << endl;
    cin >> imie;
    cout << "Podaj nazwisko" << endl;
    cin >> nazwisko;


    for (int i = 0; i < liczbaKontaktow; i++)
    {
        if (kontakty[i].imie == imie && kontakty[i].nazwisko == nazwisko)
        {
            char wybor;
            cout << "Taki kontakt istnieje. Czy na pewno chcesz wprowadzic kontakt ponownie?[t/n]" << endl;
            cin >> wybor;
            switch (wybor)
            {
            case 't':
                break;
            case 'n':
                return liczbaKontaktow;
            default:
                cout << "Wprowadz poprawny znak [t/n]" << endl;
                i--;
                break;
            }
        }
    }
    cout << "Podaj numer telefonu" << endl;
    cin.ignore();
    getline(cin, numerTelefonu);
    cout << "Podaj adres e-mail" << endl;
    cin >> adresEmail;
    cout << "Podaj adres zamieszkania" << endl;
    cin.ignore();
    getline(cin, adresZamieszkania);
    id = id+1;

    kontakty.push_back(Kontakt());
    kontakty[liczbaKontaktow].id = id;
    kontakty[liczbaKontaktow].idUzytkownika = idUzytkownika;
    kontakty[liczbaKontaktow].imie = imie;
    kontakty[liczbaKontaktow].nazwisko = nazwisko;
    kontakty[liczbaKontaktow].numerTelefonu = numerTelefonu;
    kontakty[liczbaKontaktow].adresEmail = adresEmail;
    kontakty[liczbaKontaktow].adresZamieszkania = adresZamieszkania;

    zapiszDoPliku(kontakty, liczbaKontaktow);

    cout << "Kontakt dodano pomyslnie" << endl;
    Sleep(1000);

    return kontakty.size();
}

int usunKontakt(vector<Kontakt> &kontakty, int liczbaKontaktow, int &id)
{
    system("cls");
    int pomocnicza = 0;
    int idDoUsuniecia = 0;
    fstream plik;
    char wybor;


    if (liczbaKontaktow > 0)
    {
        cout << "Podaj ID uzytkowanika, ktorego chcesz usunac:" << endl;
        cin >> idDoUsuniecia;
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            if (kontakty[i].id == idDoUsuniecia)
            {
                char wybor;
                cout << endl;
                cout << "Czy chcesz usunac ten kontakt: [t/n]" << endl;
                wyswietlKontakt (kontakty, i);
                cin >> wybor;
                cout << endl;
                switch (wybor)
                {
                case 't':
                    pomocnicza = pomocnicza + 1;
                    kontakty.erase(kontakty.begin() + i);
                    liczbaKontaktow = kontakty.size();
                    plik.open("ksiazka_adresowa.txt", ios::out | ios::trunc);
                    plik.close();
                    for (int j = 0; j < liczbaKontaktow; j++)
                    {
                        zapiszDoPliku(kontakty, j);
                    }
                    cout << "Kontakt usunieto pomyslnie" << endl;
                    Sleep(1000);
                    break;
                case 'n':
                    pomocnicza = pomocnicza + 1;
                    break;
                default:
                    cout << "Wprowadz poprawny znak [t/n]" << endl;
                    i--;
                    break;
                }
                break;
            }
            else if (i == liczbaKontaktow-1 && pomocnicza == 0)
            {
                komunikatBrakTakiegoKontaktu();
                return kontakty.size();
            }
        }
        cin.ignore();
        powrotDoMenu();
    }
    else komunikatBrakKontaktow();
    return kontakty.size();
}

void wlasciwaEdycja (vector<Kontakt> &kontakty, int &pomocnicza2, int i)
{
    char wybor;
    string zmiana;
    cout << "Co chcesz zmienic w kontakcie: " << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Nr telefonu" << endl;
    cout << "4. Adres e-mail" << endl;
    cout << "5. Adres zamieszkania" << endl;
    cout << "9. Powrot do menu" << endl;
    cout << endl;
    cin >> wybor;
    cout << endl;
    switch (wybor)
    {
    case '1':
        cout << "Podaj nowe imie: " << endl;
        cin >> zmiana;
        kontakty[i].imie = zmiana;
        break;
    case '2':
        cout << "Podaj nowe nazwisko: " << endl;
        cin >> zmiana;
        kontakty[i].nazwisko = zmiana;
        break;
    case '3':
        cout << "Podaj nowy numer telefonu: " << endl;
        cin.ignore();
        getline(cin, zmiana);
        kontakty[i].numerTelefonu = zmiana;
        break;
    case '4':
        cout << "Podaj nowy adres e-mail" << endl;
        cin >> zmiana;
        kontakty[i].adresEmail = zmiana;
        break;
    case '5':
        cout << "Podaj nowy adres zamieszkania" << endl;
        cin.ignore();
        getline(cin, zmiana);
        kontakty[i].adresZamieszkania = zmiana;
        break;
    case '9':
        pomocnicza2 = pomocnicza2 + 1;
        break;
    }
}

void edytujKontakt (vector<Kontakt> &kontakty, int liczbaKontaktow, int &id)
{
    system("cls");
    int pomocnicza = 0;
    int pomocnicza2 = 0;
    int idDoEdycji = 0;
    fstream plik;
    char wybor;

    if (liczbaKontaktow > 0)
    {
        cout << "Podaj ID uzytkowanika, ktorego chcesz edytowac:" << endl;
        cin >> idDoEdycji;
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            if (kontakty[i].id == idDoEdycji)
            {
                char wybor;
                cout << endl;
                cout << "Czy chcesz edytowac ten kontakt: [t/n]" << endl;
                wyswietlKontakt (kontakty, i);
                cin >> wybor;
                cout << endl;
                switch (wybor)
                {
                case 't':
                    pomocnicza = pomocnicza + 1;
                    wlasciwaEdycja (kontakty, pomocnicza2, i);
                    plik.open("ksiazka_adresowa.txt", ios::out | ios::trunc);
                    plik.close();
                    for (int j = 0; j < liczbaKontaktow; j++)
                    {
                        zapiszDoPliku(kontakty, j);
                    }
                    if (pomocnicza2 == 0)
                    {
                        cout << "Kontakt edytowano pomyslnie" << endl;
                        Sleep(1000);
                    }
                    break;
                case 'n':
                    pomocnicza = pomocnicza + 1;
                    break;
                default:
                    cout << "Wprowadz poprawny znak [t/n]" << endl;
                    i--;
                    break;
                }
                continue;
            }
            else if (i == liczbaKontaktow-1 && pomocnicza == 0)
            {
                komunikatBrakTakiegoKontaktu();
                break;
            }
        }
        if (pomocnicza > 0 && pomocnicza2 == 0)
        {
            cin.ignore();
            powrotDoMenu();
        }
    }
    else komunikatBrakKontaktow();
}
//
//void wlaczKsiazke (int idUzytkownika)
//{
//    int liczbaKontaktow = 0;
//    vector<Kontakt>kontakty;
//    char wybor;
//    int id = 0, wylogowujaca = 0;
//    liczbaKontaktow = odczytZPliku (kontakty, id);
//
////INTERFEJS______________________________________
//    while(wylogowujaca == 0)
//    {
//        system("cls");
//        cout << "KSIAZKA ADRESOWA" << endl;
//        cout << "1. Dodaj adresata" << endl;
//        cout << "2. Wyszukaj po imieniu" << endl;
//        cout << "3. Wyszukaj po nazwisku" << endl;
//        cout << "4. Wyswietl wszystkich adresatow" << endl;
//        cout << "5. Usun adresata" << endl;
//        cout << "6. Edytuj adresata" << endl;
//        cout << "7. Wyloguj" << endl;
//        cout << "9. Zakoncz program" << endl;
//        cout << "Twoj wybor: " << endl;
//        cin >> wybor;
//
//        switch (wybor)
//        {
//        case '1':
//            liczbaKontaktow = dodajKontakt(kontakty, liczbaKontaktow, id, idUzytkownika);
//            break;
//        case '2':
//            wyszukajPoImieniu(kontakty, liczbaKontaktow);
//            break;
//        case '3':
//            wyszukajPoNazwisku(kontakty, liczbaKontaktow);
//            break;
//        case '4':
//            wyswietlKontakty(kontakty, liczbaKontaktow);
//            break;
//        case '5':
//            liczbaKontaktow = usunKontakt(kontakty, liczbaKontaktow, id);
//            break;
//        case '6':
//            edytujKontakt(kontakty, liczbaKontaktow, id);
//            break;
//        case '7':
//            wylogowujaca++;
//            break;
//        case '9':
//            exit(0);
//            break;
//        }
//    }
//}

void zapiszDoPlikuUzytkownicy (vector<Uzytkownik> &uzytkownicy, int liczbaUzytkownikow)
{
    char pipe = '|';
    fstream plik;
    plik.open("uzytkownicy.txt", ios::out | ios::app);
    plik << uzytkownicy[liczbaUzytkownikow].idUzytkownika << pipe;
    plik << uzytkownicy[liczbaUzytkownikow].login << pipe;
    plik << uzytkownicy[liczbaUzytkownikow].haslo << pipe << endl;
    plik.close();
}

int odczytZPlikuUzytkownicy (vector<Uzytkownik> &uzytkownicy, int &idUzytkownika)
{
    int nrPipe = 0;
    int i = 0;
    char pipe = '|';
    string wycietaFraza = "";
    string linia;
    fstream plik;

    plik.open("uzytkownicy.txt", ios::in);
    if(plik.good() == false)
    {
        cout << "Plik uzytkownicy.txt nie istnieje!";
    }
    while(getline(plik,linia))
    {
        uzytkownicy.push_back(Uzytkownik());
        while(linia!="")
        {
            size_t pozycja = linia.find(pipe);
            wycietaFraza = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);
            nrPipe++;

            switch(nrPipe)
            {
            case 1:
                uzytkownicy[i].idUzytkownika = atoi(wycietaFraza.c_str());
                //idUzytkownika = uzytkownicy[i].idUzytkownika;
                break;
            case 2:
                uzytkownicy[i].login = wycietaFraza;
                break;
            case 3:
                uzytkownicy[i].haslo = wycietaFraza;
                break;
            }
            wycietaFraza = "";
        }
        idUzytkownika = uzytkownicy[i].idUzytkownika;
        i++;
        nrPipe = 0;
    }
    plik.close();

    return idUzytkownika;
}

int dodajUzytkownika (vector<Uzytkownik> &uzytkownicy, int liczbaUzytkownikow, int &idUzytkownika)
{
    system("cls");
    char pipe = '|';
    string login, haslo;
    cout << "Podaj login" << endl;
    cin >> login;

    for (int i = 0; i < liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].login == login)
        {
            cout << "Taki uzytkownik juz istnieje. Wprowadz inna nazwe uzytkownika:" << endl;
            cin >> login;
            i = 0;
        }
    }
    cout << "Podaj haslo" << endl;
    cin >> haslo;

    idUzytkownika = idUzytkownika+1;

    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[liczbaUzytkownikow].idUzytkownika = idUzytkownika;
    uzytkownicy[liczbaUzytkownikow].login = login;
    uzytkownicy[liczbaUzytkownikow].haslo = haslo;

    zapiszDoPlikuUzytkownicy(uzytkownicy, liczbaUzytkownikow);

    cout << "Uzytkownik zarejestrowany prawdlowo" << endl;
    Sleep(1000);

    return liczbaUzytkownikow+1;
}


int main()
{
    int liczbaUzytkownikow = 0;
    vector<Uzytkownik>uzytkownicy;
    char wybor;
    int idUzytkownika = 0;
    liczbaUzytkownikow = odczytZPlikuUzytkownicy (uzytkownicy, idUzytkownika);
    //INTERFEJS______________________________________
    while(1)
    {
        system("cls");
        cout << "MENU GLOWNE" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "Twoj wybor: " << endl;
        cin >> wybor;

        switch (wybor)
        {
        case '1':
            liczbaUzytkownikow = dodajUzytkownika(uzytkownicy, liczbaUzytkownikow, idUzytkownika);
            break;
        case '9':
            exit(0);
            break;
        }
    }
    return 0;
}
