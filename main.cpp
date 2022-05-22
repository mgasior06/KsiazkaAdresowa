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

void czyPlikIstnieje (string nazwaPliku)
{
    fstream plik;
    plik.open(nazwaPliku, ios::in);
    if(!plik.good())
    {
        cout << "Plik " << nazwaPliku << " nie istnieje!";
    }
    plik.close();
}

Kontakt odczytPojedynczegoKontaktu(Kontakt &kontakt, fstream &plik, string linia)
{
    int nrKreski = 0;
    string wycietaFraza = "";
    while(linia!="")
    {
        size_t pozycjaKreski = linia.find('|');
        wycietaFraza = linia.substr(0,pozycjaKreski);
        linia.erase(0,pozycjaKreski+1);
        nrKreski++;

        switch(nrKreski)
        {
        case 1:
            kontakt.id = atoi(wycietaFraza.c_str());
            break;
        case 2:
            kontakt.idUzytkownika = atoi(wycietaFraza.c_str());
            break;
        case 3:
            kontakt.imie = wycietaFraza;
            break;
        case 4:
            kontakt.nazwisko = wycietaFraza;
            break;
        case 5:
            kontakt.numerTelefonu = wycietaFraza;
            break;
        case 6:
            kontakt.adresEmail = wycietaFraza;
            break;
        case 7:
            kontakt.adresZamieszkania = wycietaFraza;
            break;
        }
        wycietaFraza = "";
    }
    return kontakt;
}

int odczytZPlikuKsiazkaAdresowa (vector<Kontakt> &kontakty, int &idKontaktu, int idZalogowanegoUzytkownika)
{
    string nazwaPliku = "ksiazka_adresowa.txt", linia = "";
    fstream plik;
    czyPlikIstnieje(nazwaPliku);
    Kontakt kontakt;

    plik.open(nazwaPliku, ios::in);
    while(getline(plik,linia))
    {
        odczytPojedynczegoKontaktu(kontakt, plik, linia);
        idKontaktu = kontakt.id;
        if (kontakt.idUzytkownika == idZalogowanegoUzytkownika)
        {
            kontakty.push_back(kontakt);
        }
    }
    plik.close();
    cout << idKontaktu << endl;
    system("pause");
    return idKontaktu;
}

void zapiszDoPliku (vector<Kontakt> &kontakty, int liczbaKontaktow)
{
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    plik << kontakty[liczbaKontaktow].id << '|';
    plik << kontakty[liczbaKontaktow].idUzytkownika << '|';
    plik << kontakty[liczbaKontaktow].imie << '|';
    plik << kontakty[liczbaKontaktow].nazwisko << '|';
    plik << kontakty[liczbaKontaktow].numerTelefonu << '|';
    plik << kontakty[liczbaKontaktow].adresEmail << '|';
    plik << kontakty[liczbaKontaktow].adresZamieszkania << '|' << endl;
    plik.close();
}

int zapisDoPlikuPoUsuwaniu(vector<Kontakt> &kontakty, int idUsuwanegoKontaktu)
{
    Kontakt kontakt;
    int ostatnieId = 0;

    fstream plikOdczyt, plikZapis;
    string nazwaPlikuOdczyt = "ksiazka_adresowa.txt";
    czyPlikIstnieje(nazwaPlikuOdczyt);
    string nazwaPlikuZapis = "ksiazka_adresowa_tymczasowa.txt";
    czyPlikIstnieje(nazwaPlikuOdczyt);

    string wycietaFraza = "", linia = "";

    plikOdczyt.open("ksiazka_adresowa.txt", ios::in);
    while(getline(plikOdczyt,linia))
    {
        odczytPojedynczegoKontaktu(kontakt, plikOdczyt, linia);

        if (kontakt.id != idUsuwanegoKontaktu)
        {
            plikZapis.open("ksiazka_adresowa_tymczasowa.txt", ios::out | ios::app);
            plikZapis << kontakt.id << '|';
            plikZapis << kontakt.idUzytkownika << '|';
            plikZapis << kontakt.imie << '|';
            plikZapis << kontakt.nazwisko << '|';
            plikZapis << kontakt.numerTelefonu << '|';
            plikZapis << kontakt.adresEmail << '|';
            plikZapis << kontakt.adresZamieszkania << '|' << endl;
            plikZapis.close();
            ostatnieId = kontakt.id;
        }
        else
        {
            continue;
        }
    }
    plikOdczyt.close();
    remove("ksiazka_adresowa.txt");
    rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt");
    return ostatnieId;

}

void zapisDoPlikuTymczasowego(vector<Kontakt> &kontakty, int idEdytowanegoKontaktu, int i)
{
    Kontakt kontakt;

    fstream plikOdczyt, plikZapis;
    string nazwaPlikuOdczyt = "ksiazka_adresowa.txt";
    czyPlikIstnieje(nazwaPlikuOdczyt);
    string nazwaPlikuZapis = "ksiazka_adresowa_tymczasowa.txt";
    czyPlikIstnieje(nazwaPlikuOdczyt);

    string wycietaFraza = "", linia = "";

    plikOdczyt.open("ksiazka_adresowa.txt", ios::in);
    while(getline(plikOdczyt,linia))
    {
        odczytPojedynczegoKontaktu(kontakt, plikOdczyt, linia);

        if (kontakt.id != idEdytowanegoKontaktu)
        {
            plikZapis.open("ksiazka_adresowa_tymczasowa.txt", ios::out | ios::app);
            plikZapis << kontakt.id << '|';
            plikZapis << kontakt.idUzytkownika << '|';
            plikZapis << kontakt.imie << '|';
            plikZapis << kontakt.nazwisko << '|';
            plikZapis << kontakt.numerTelefonu << '|';
            plikZapis << kontakt.adresEmail << '|';
            plikZapis << kontakt.adresZamieszkania << '|' << endl;
            plikZapis.close();
        }
        else
        {
            plikZapis.open("ksiazka_adresowa_tymczasowa.txt", ios::out | ios::app);
            plikZapis << kontakty[i].id << '|';
            plikZapis << kontakty[i].idUzytkownika << '|';
            plikZapis << kontakty[i].imie << '|';
            plikZapis << kontakty[i].nazwisko << '|';
            plikZapis << kontakty[i].numerTelefonu << '|';
            plikZapis << kontakty[i].adresEmail << '|';
            plikZapis << kontakty[i].adresZamieszkania << '|' << endl;
            plikZapis.close();

        }
    }
    plikOdczyt.close();
    remove("ksiazka_adresowa.txt");
    rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt");
}

string wczytajLinie()
{
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    getline(cin, wejscie);
    char znak = wejscie[0];
    return znak;
}

int wczytajLiczbe()
{
    int liczba = 0;
    string wejscie = "";
    getline(cin, wejscie);
    liczba = atoi(wejscie.c_str());
    return liczba;
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
    cout << "Brak zapisanych kontaktow.\n" << endl;
    powrotDoMenu();
}

void komunikatBrakTakiegoKontaktu ()
{
    cout << "Brak takiego kontaktu.\n" << endl;
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
        imie = wczytajLinie();
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
        nazwisko = wczytajLinie();
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
        powrotDoMenu();
    }
    else komunikatBrakKontaktow();
}

int dodajKontakt (vector<Kontakt> &kontakty, int liczbaKontaktow, int &id, int idUzytkownika)
{
    system("cls");
    string imie, nazwisko, numerTelefonu, adresEmail, adresZamieszkania;
    cout << "Podaj imie\n";
    imie = wczytajLinie();
    cout << "Podaj nazwisko\n";
    nazwisko = wczytajLinie();

    for (int i = 0; i < liczbaKontaktow; i++)
    {
        if (kontakty[i].imie == imie && kontakty[i].nazwisko == nazwisko)
        {
            char wybor;
            cout << "Taki kontakt istnieje. Czy na pewno chcesz wprowadzic kontakt ponownie?[t/n]\n";
            wybor = wczytajZnak();
            switch (wybor)
            {
            case 't':
                break;
            case 'n':
                return liczbaKontaktow;
            default:
                cout << "Wprowadz poprawny znak [t/n]\n";
                i--;
                break;
            }
        }
    }
    cout << "Podaj numer telefonu\n";
    numerTelefonu = wczytajLinie();
    cout << "Podaj adres e-mail\n";
    adresEmail = wczytajLinie();
    cout << "Podaj adres zamieszkania\n";
    adresZamieszkania = wczytajLinie();


    id = id + 1;
    cout << "ID do zapisu: " << id << endl;
    system("pause");

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
        cout << "Podaj ID uzytkownika, ktorego chcesz usunac:\n";
        idDoUsuniecia = wczytajLiczbe();
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            if (kontakty[i].id == idDoUsuniecia)
            {
                cout << "\nCzy chcesz usunac ten kontakt: [t/n]\n";
                wyswietlKontakt (kontakty, i);
                wybor = wczytajZnak();
                cout << endl;
                switch (wybor)
                {
                case 't':
                    pomocnicza = pomocnicza + 1;
                    kontakty.erase(kontakty.begin() + i);
                    liczbaKontaktow = kontakty.size();
                    id = zapisDoPlikuPoUsuwaniu(kontakty, idDoUsuniecia);
                    cout << "Kontakt usunieto pomyslnie\n";
                    Sleep(1000);
                    break;
                case 'n':
                    pomocnicza = pomocnicza + 1;
                    break;
                default:
                    cout << "Wprowadz poprawny znak [t/n]\n";
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
    wybor = wczytajZnak();
    cout << endl;
    switch (wybor)
    {
    case '1':
        cout << "Podaj nowe imie: " << endl;
        zmiana = wczytajLinie();
        kontakty[i].imie = zmiana;
        break;
    case '2':
        cout << "Podaj nowe nazwisko: " << endl;
        zmiana = wczytajLinie();
        kontakty[i].nazwisko = zmiana;
        break;
    case '3':
        cout << "Podaj nowy numer telefonu: " << endl;
        zmiana = wczytajLinie();
        kontakty[i].numerTelefonu = zmiana;
        break;
    case '4':
        cout << "Podaj nowy adres e-mail" << endl;
        zmiana = wczytajLinie();
        kontakty[i].adresEmail = zmiana;
        break;
    case '5':
        cout << "Podaj nowy adres zamieszkania" << endl;
        zmiana = wczytajLinie();
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
    char wybor;

    if (liczbaKontaktow > 0)
    {
        cout << "Podaj ID uzytkowanika, ktorego chcesz edytowac:\n";
        idDoEdycji = wczytajLiczbe();
        for (int i = 0; i < liczbaKontaktow; i++)
        {
            if (kontakty[i].id == idDoEdycji)
            {
                cout << "\nCzy chcesz edytowac ten kontakt: [t/n]\n";
                wyswietlKontakt (kontakty, i);
                wybor = wczytajZnak();
                cout << endl;
                switch (wybor)
                {
                case 't':
                    pomocnicza = pomocnicza + 1;
                    wlasciwaEdycja (kontakty, pomocnicza2, i);

                    zapisDoPlikuTymczasowego (kontakty, idDoEdycji, i);

                    if (pomocnicza2 == 0)
                    {
                        cout << "Kontakt edytowano pomyslnie\n";
                        Sleep(1000);
                    }
                    break;
                case 'n':
                    pomocnicza = pomocnicza + 1;
                    break;
                default:
                    cout << "Wprowadz poprawny znak [t/n]\n";
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
            powrotDoMenu();
        }
    }
    else komunikatBrakKontaktow();
}

void zapiszDoPlikuUzytkownicy (Uzytkownik &uzytkownik)
{
    fstream plik;
    plik.open("uzytkownicy.txt", ios::out | ios::app);
    plik << uzytkownik.idUzytkownika << '|';
    plik << uzytkownik.login << '|';
    plik << uzytkownik.haslo << '|' << endl;
    plik.close();
}

void zmienHaslo (vector<Uzytkownik> &uzytkownicy, int idUzytkownika)
{
    system("cls");
    string stareHaslo = "", noweHaslo = "";
    Uzytkownik uzytkownik;
    cout << "ZMIANA HASLA\n";
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr->idUzytkownika == idUzytkownika)
        {
            for (int i = 3; i >= 0; i--)
            {
                cout << "Podaj haslo:\n";
                stareHaslo = wczytajLinie();
                if (itr->haslo == stareHaslo)
                {
                    cout << "Podaj nowe haslo:\n";
                    noweHaslo = wczytajLinie();
                    itr->haslo = noweHaslo;
                    remove("uzytkownicy.txt");
                    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
                    {
                        uzytkownik.idUzytkownika = itr->idUzytkownika;
                        uzytkownik.login = itr->login;
                        uzytkownik.haslo = itr->haslo;
                        zapiszDoPlikuUzytkownicy(uzytkownik);
                    }
                    cout << "Haslo zostalo zmienione.\n";
                    Sleep(1000);
                    break;
                }
                else
                {
                    cout << "\nPodane haslo jest nieprawidlowe.\n";
                    if (i > 0)
                    {
                        if (i == 1)
                        {
                            cout << "Uzytkownik zablokowany na 3 s...\n\n";
                            Sleep(3000);
                            powrotDoMenu();
                            break;
                        }
                        cout << "Wpisz haslo ponownie, pozostalo prob: " << i-1 << "\n";
                        continue;
                    }
                }
            }
        }

    }


}

void wlaczKsiazke (int idUzytkownika, vector<Uzytkownik> &uzytkownicy)
{
    int liczbaKontaktow = 0;
    vector<Kontakt>kontakty;
    char wybor;
    int idKontaktu = 0, wylogowujaca = 0;
    idKontaktu = odczytZPlikuKsiazkaAdresowa (kontakty, idKontaktu, idUzytkownika);
    liczbaKontaktow = kontakty.size();

    while(wylogowujaca == 0)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA\n";
        cout << "1. Dodaj adresata\n";
        cout << "2. Wyszukaj po imieniu\n";
        cout << "3. Wyszukaj po nazwisku\n";
        cout << "4. Wyswietl wszystkich adresatow\n";
        cout << "5. Usun adresata\n";
        cout << "6. Edytuj adresata\n";
        cout << "7. Zmien haslo\n";
        cout << "8. Wyloguj\n";
        cout << "9. Zakoncz program\n";
        cout << "Twoj wybor: \n";
        wybor = wczytajZnak();

        switch (wybor)
        {
        case '1':
            liczbaKontaktow = dodajKontakt(kontakty, liczbaKontaktow, idKontaktu, idUzytkownika);
            break;
        case '2':
            wyszukajPoImieniu(kontakty, liczbaKontaktow);
            break;
        case '3':
            wyszukajPoNazwisku(kontakty, liczbaKontaktow);
            break;
        case '4':
            wyswietlKontakty(kontakty, liczbaKontaktow);
            break;
        case '5':
            liczbaKontaktow = usunKontakt(kontakty, liczbaKontaktow, idKontaktu);
            break;
        case '6':
            edytujKontakt(kontakty, liczbaKontaktow, idKontaktu);
            break;
        case '7':
            zmienHaslo(uzytkownicy, idUzytkownika);
            break;
        case '8':
            wylogowujaca++;
            break;
        case '9':
            exit(0);
            break;
        default:
            continue;
        }
    }
}

void odczytZPlikuUzytkownicy (vector<Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string nazwaPliku = "uzytkownicy.txt", wycietaFraza = "", linia = "";
    czyPlikIstnieje(nazwaPliku);
    int nrKreski = 0;
    Uzytkownik uzytkownik;

    plik.open("uzytkownicy.txt", ios::in);
    while(getline(plik,linia))
    {
        while(linia!="")
        {
            size_t pozycjaKreski = linia.find('|');
            wycietaFraza = linia.substr(0,pozycjaKreski);
            linia.erase(0,pozycjaKreski+1);
            nrKreski++;

            switch(nrKreski)
            {
            case 1:
                uzytkownik.idUzytkownika = atoi(wycietaFraza.c_str());
                break;
            case 2:
                uzytkownik.login = wycietaFraza;
                break;
            case 3:
                uzytkownik.haslo = wycietaFraza;
                break;
            }
            wycietaFraza = "";
        }
        uzytkownicy.push_back(uzytkownik);
        nrKreski = 0;
    }
    plik.close();
}

void dodajUzytkownika (vector<Uzytkownik> &uzytkownicy)
{
    system("cls");
    Uzytkownik uzytkownik;
    int idUzytkownika = 1;
    string login, haslo;
    cout << "Podaj login" << endl;
    login = wczytajLinie();
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr->login == login)
        {
            cout << "Taki uzytkownik juz istnieje. Wprowadz inna nazwe uzytkownika:\n";
            login = wczytajLinie();
            itr = uzytkownicy.begin();
        }
        idUzytkownika = itr->idUzytkownika + 1;
    }
    cout << "Podaj haslo:" << endl;
    haslo = wczytajLinie();

    uzytkownik.idUzytkownika = idUzytkownika;
    uzytkownik.login = login;
    uzytkownik.haslo = haslo;

    uzytkownicy.push_back(uzytkownik);

    zapiszDoPlikuUzytkownicy(uzytkownik);

    cout << "Uzytkownik zarejestrowany prawidlowo.\n";
    Sleep(1000);
}

void logowanie (vector<Uzytkownik> &uzytkownicy)
{
    if (!uzytkownicy.empty())
    {
        string login = "", haslo = "";
        int pomocnicza = 0;

        system("cls");
        cout << "LOGOWANIE\n" << endl;
        cout << "Podaj login:" << endl;
        login = wczytajLinie();


        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            if (itr->login == login)
            {
                pomocnicza++;
                for (int i = 3; i >= 0; i--)
                {
                    cout << "Podaj haslo:\n";
                    haslo = wczytajLinie();
                    if (itr->haslo == haslo)
                    {
                        cout << "Uzytkownik poprawnie zalogowany.\n";
                        Sleep(1000);
                        wlaczKsiazke (itr->idUzytkownika, uzytkownicy);
                        break;
                    }
                    else
                    {
                        cout << "\nPodane haslo jest nieprawidlowe.\n";
                        if (i > 0)
                        {
                            if (i == 1)
                            {
                                cout << "Uzytkownik zablokowany na 3 s...\n\n";
                                Sleep(3000);
                                powrotDoMenu();
                                break;
                            }
                            cout << "Zaloguj sie ponownie, pozostalo prob: " << i-1 << "\n";
                            continue;
                        }
                    }
                }
            }
        }
        if (pomocnicza == 0)
        {
            cout << "\nBrak uzytkownika o podanym loginie.\n\n";
            powrotDoMenu();
        }
    }
    else
    {
        cout << "\nBrak zarejestrowanych uzytkownikow.\n\n";
        powrotDoMenu();
    }
}

int main()
{
    int liczbaUzytkownikow = 0;
    vector<Uzytkownik>uzytkownicy;
    char wybor;
    odczytZPlikuUzytkownicy (uzytkownicy);

    while(true)
    {
        system("cls");
        cout << "MENU GLOWNE" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: " << endl;

        wybor = wczytajZnak();
        switch (wybor)
        {
        case '1':
            dodajUzytkownika(uzytkownicy);
            break;
        case '2':
            logowanie (uzytkownicy);
            break;
        case '9':
            exit(0);
            break;
        default:
            continue;
        }
    }
    return 0;
}
