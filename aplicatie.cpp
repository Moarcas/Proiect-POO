#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <memory>
#include <stdexcept>
#include "persoana.h"

using MyMapUtilizatori = std::map<int, Persoana*>;

class Aplicatie {
    MyMapUtilizatori utilizatori;

public:
    Aplicatie();
    void AfisareUtilizatori();
    bool AdaugareUtilizator();
    bool StergereUtilizator(int index);
    bool AccesareProfil();
    void SalvareDate();
};


Aplicatie::Aplicatie() {
    Persoana *p;
    char sex;
    int index;

    std::ifstream f;

    f.open("utilizatori.txt");

    if(!f) {
        std::cout << "Eroare la deschiderea fisierului";
        return;
    }
    while(f.get(sex)) {
        if(sex == 'm')
            p = new Baiat(), std::cout << "Baiat";
        else
            if(sex == 'f')
                p = new Fata(), std::cout << "Fata";
            else
                continue;
        f >> *p;
        utilizatori[p->GetIndexPersoana()] = p;
    }

    Persoana::numar_persoane = utilizatori.size();

    f.close();
}

bool Aplicatie::AdaugareUtilizator() {
    char sex;
    Persoana *p;

    std::cout << "Va rog introduceti datele dumneavoastra: \n";

    std::cout << "Sex (m/f): ";
    std::cin.ignore(1000, '\n');
    std::cin.get(sex);

    if(sex == 'm') {
        p = new Baiat();
    }
    else
        if(sex == 'f') {
            p = new Fata();
        }
        else
            return false;

    std::cin >> *p;
    utilizatori[p->GetIndexPersoana()] = p;

    return true;
}

void Aplicatie::SalvareDate() {
    std::ofstream g;
    g.open("utilizatori.txt");

    for(const auto& elem : utilizatori)
    {
        if(typeid(*elem.second).name() == typeid(Baiat).name()) {
            g << "m ";
        }
        else
            g << "f ";
        g << *elem.second;
    }

    g.close();
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

bool Aplicatie::StergereUtilizator(int index) {
    Persoana *p = utilizatori[index];
    std::string parola;
    std::string alegere;
    std::cout << "Introduceti parola: ";
    std::cin >> parola;

    while(parola != p->parola) {
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
            return false;
        }
    }

    utilizatori.erase(index);
    return true;
}

bool Aplicatie::AccesareProfil() {
    int index;
    int ok = 1;
    std::cout << "Introduceti indexul profilului pe care doriti sa il accesati\n";
    std::cout << "Raspuns: ";
    std::cin >> index;
    std::cout << '\n';

    if(utilizatori.find(index) == utilizatori.end())
        return false;

    Persoana *p = utilizatori[index];
    std::string parola;
    std::string alegere;
    std::cout << "Introduceti parola: ";
    std::cin >> parola;

    while(parola != p->parola) {
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
            return false;
        }
        std::cout << "Optiune invalida!\n";
    }

    std::cout << "\nProfil accesat cu succes\n";

    do {
        for(auto masa = p->mese.begin(); masa != p->mese.end(); masa++) {
            std::cout << *masa;
            std::cout << "\n-----------------------------------\n";
        }

        std::cout << "\nBuna " << p->GetNumePersoana() << "! Alege una dintre optiunile de mai jos\n";
        std::cout << "\t1 - Afisare tip corp\n";
        std::cout << "\t2 - Afisare greutate ideala\n";
        std::cout << "\t3 - Afisare numar calorii necesare\n";
        std::cout << "\t4 - Afisare procentaj grasime\n";
        std::cout << "\t5 - Stergere profil\n";
        std::cout << "\t6 - Iesire\n";
        std::cout << "\t7 - Adaugare masa\n";

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
            if(StergereUtilizator(index)) {
                std::cout << "\nProfil sters cu succes\n\n";
                ok = 0;
                continue;
            }
            else {
                std::cout << "\n Eroare la stergerea profilului\n\n";
            }
        }
        if(alegere == "6") {
            ok = 0;
            continue;
        }

        if(alegere == "7") {
            p->AdaugareMasa();
            continue;
        }
        std::cout << "Optiune invalida!\n";
    }while(ok);
    for(int i = 0; i < p->mese.size(); i++) {
        std::cout << p->mese[i] << '\n';
    }
    delete p;
    return true;
}

void CitireAlegere(int &alegere) {
    // fflush(stdin);
    std::cin.clear();
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
    throw std::invalid_argument("alegerea nu exista");
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
        catch(const std::invalid_argument& e) {
            std::cout << e.what();
            continue;
        }

        switch(alegere) {
            case 1:
                if(a.AdaugareUtilizator()) {
                    std::cout << "\nUtilizator adaugat cu succes!\n\n";
                }
                else {
                    std::cout << "\nEroare la crearea utilizatorului\n\n";
                }
                break;

            case 2:
                if(!a.AccesareProfil()) {
                    std::cout << "\nEroare la accesarea profilului\n\n";
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
