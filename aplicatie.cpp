#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include "persoana.h"

typedef std::map<int, Persoana*> MyMapUtilizatori;
typedef std::map<int, std::string> MyMapParole;
// typedef std::pair<int, Persoana*> MyPair;

class Aplicatie {
    MyMapUtilizatori utilizatori;
    MyMapParole parole;

public:
    Aplicatie();
    void AfisareUtilizatori();
    void AdaugareUtilizator();
    void StergereUtilizator(int index);
    void CreareParola(int index);
    void AccesareProfil();
    void SalvareDate();
};

Aplicatie::Aplicatie() {
    Persoana *p;
    char sex;
    int index;
    std::string parola;

    std::ifstream f;
    std::ifstream f_parole;

    f.open("utilizatori.txt");
    f_parole.open("parole.txt");

    if(!f || !f_parole) {
        std::cout << "Eroare la deschiderea fisierului";
        return;
    }
    while(!f.eof()) {
        f.get(sex);
        switch (sex) {
            case 'm':
                p = new Baiat();
                f >> *p;
                utilizatori[p->GetIndexPersoana()] = p;
                break;

            case 'f':
                p = new Fata();
                f >> *p;
                utilizatori[p->GetIndexPersoana()] = p;
                break;

            default:
                break;
        }
    }

    while(!f_parole.eof()) {
        f_parole >> index >> parola;
        parole[index] = parola;
    }

    f.close();
    f_parole.close();
}

void Aplicatie::AdaugareUtilizator() {
    char sex;
    Persoana *p;

    std::cout << "Va rog introduceti datele dumneavoastra: \n";

    std::cout << "Sex (m/f): ";
    fflush(stdin);
    std::cin.get(sex);

    switch (sex) {
        case 'm':
            p = new Baiat();
            std::cin >> *p;
            utilizatori[p->GetIndexPersoana()] = p;
            break;
        case 'f':
            p = new Fata();
            std::cin >> *p;
            utilizatori[p->GetIndexPersoana()] = p;
            break;
        default:
            throw 0;
            break;
    }

    CreareParola(p->GetIndexPersoana());

    std::cout << "\nUtilizator adaugat cu succes!\n\n";
    std::cout << "Datele contului creat:\n";
    std::cout << *p << '\n';
}

void Aplicatie::CreareParola(int index) {
    std::string parola, parola_aux;

    while(true) {
        std::cout << "Alegeti o parola: ";
        std::cin >> parola;
        std::cout << "Reintroduceti parola: ";
        std::cin >> parola_aux;
        if(parola == parola_aux) {
            parole[index] = parola;
            return;
        }
        std::cout << "Parole diferite! Incercati din nou\n";
        std::cin.get();
    }
}

void Aplicatie::SalvareDate() {
    std::ofstream g;
    std::ofstream g_parole;
    g.open("utilizatori.txt");
    g_parole.open("parole.txt");

    for(const auto& elem : utilizatori)
    {
        const char *tip = typeid(*elem.second).name();
        const char *b = "Baiat";
        if(strstr(tip, b))
            g << "m ";
        else
            g << "f ";

        g << *elem.second;
    }

    for(const auto& elem : parole) {
        g_parole << elem.first << " " << elem.second << '\n';
    }

    g.close();
    g_parole.close();
}

void Aplicatie::AfisareUtilizatori() {
    if(utilizatori.empty())
        std::cout << "Nu exista profile create\n";
    else {
        std::cout << "Profilele create sunt:\n\n";
        for(const auto& elem : utilizatori)
        {
            std::cout << *elem.second << "\n";
        }
    }
}

void Aplicatie::StergereUtilizator(int index) {
    std::string parola;
    std::string alegere;
    std::cout << "Introduceti parola: ";
    std::cin >> parola;

    while(parola != parole[index]) {
        std::cout << "Parola incorecta!\n";
        std::cout << "Selectati una dintre optiunile de mai jos\n";
        std::cout << "\t1 - Incearca din nou\n";
        std::cout << "\t2 - Anuleaza\n";

        std::cout << "Raspuns: ";
        std::cin >> alegere;

        if(alegere == "1") {
            std::cout << "Introduceti parola: ";
            std::cin >> parola;
            continue;
        }
        if(alegere == "2") {
            throw 1;
        }
        std::cout << "Optiune invalida!\n";
    }

    utilizatori.erase(index);
    parole.erase(index);
    std::cout << "Profil sters cu succes\n";
}

void Aplicatie::AccesareProfil() {
    int index;
    std::cout << "Introduceti indexul profilului pe care doriti sa il accesati\n";
    std::cout << "Raspuns: ";
    std::cin >> index;
    std::cout << '\n';

    if(utilizatori.find(index) == utilizatori.end())
        throw 1;

    std::string parola;
    std::string alegere;
    std::cout << "Introduceti parola: ";
    std::cin >> parola;

    while(parola != parole[index]) {
        std::cout << "Parola incorecta!\n";
        std::cout << "Selectati una dintre optiunile de mai jos\n";
        std::cout << "\t1 - Incearca din nou\n";
        std::cout << "\t2 - Anuleaza\n";

        std::cout << "Raspuns: ";
        std::cin >> alegere;
        std::cout << '\n';

        if(alegere == "1") {
            std::cout << "Introduceti parola: ";
            std::cin >> parola;
            continue;
        }
        if(alegere == "2") {
            return;
        }
        std::cout << "Optiune invalida!\n";
    }

    std::cout << "\nProfil accesat cu succes\n";

    Persoana *p = utilizatori[index];
    do {
        std::cout << "\nBuna " << p->GetNumePersoana() << "! Alege una dintre optiunile de mai jos\n";
        std::cout << "\t1 - Afisare tip corp\n";
        std::cout << "\t2 - Afisare greutate ideala\n";
        std::cout << "\t3 - Afisare numar calorii necesare\n";
        std::cout << "\t4 - Afisare procentaj grasime\n";
        std::cout << "\t5 - Stergere profil\n";
        std::cout << "\t6 - Iesire\n";

        std::cout << "Raspuns: ";
        std::cin >> alegere;

        if(alegere == "1") {
            p->AfisareTipCorp();
            continue;
        }
        if(alegere == "2") {
            p->AfisareGreutateIdeala();
            continue;
        }
        if(alegere == "3") {
            p->AfisareNumarCaloriiNecesare();
            continue;
        }
        if(alegere == "4") {
            p->AfisareProcentajGrasime();
            continue;
        }
        if(alegere == "5") {
            try {
                StergereUtilizator(index);
                return;
            }
            catch(int x) {
                continue;
            }
            return;
        }
        if(alegere == "6")
            return;
        std::cout << "Optiune invalida!\n";
    }while(true);

}

void CitireAlegere(int &alegere) {
    fflush(stdin);
    std::string input;
    std::cin >> input;

    if(input == "1") {
        alegere = 1;
        return;
    }
    if(input == "2") {
        alegere = 2;
        return;
    }
    if(input == "3") {
        alegere = 3;
        return;
    }
    if(input == "4") {
        alegere = 4;
        return;
    }
    throw 0;
}

int main() {
    Aplicatie a;
    int alegere;
    std::cout << "Aplicatie calorii\n";

    do {
        std::cout << "\nAlege una dintre optiunile de mai jos\n";
        std::cout << "\t1 - Creeaza un profil\n";
        std::cout << "\t2 - Accesare profil\n";
        std::cout << "\t3 - Afisare profile\n";
        std::cout << "\t4 - Iesire\n";

        std::cout << "Raspuns: ";

        try {
            CitireAlegere(alegere);
        }
        catch(int x) {
            std::cout << "Optiune invalida!\n";
            continue;
        }

        switch(alegere) {
            case 1:
                try {
                    a.AdaugareUtilizator();
                }
                catch(int x) {
                    std::cout << "Optiune invalida!\n";
                }
                break;

            case 2:
                try {
                    a.AccesareProfil();
                }
                catch(int x) {
                    std::cout << "Indexul introdus nu este valid!\n";
                }
                break;

            case 3:
                a.AfisareUtilizatori();
                break;

            case 4:
                a.SalvareDate();
                break;
            default:
                std::cout << "Optiune invalida!\n";
                break;
        }
    }while(alegere != 4);

    return 0;
}
