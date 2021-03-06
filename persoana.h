#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include "masa.h"

class Persoana {
protected:
    std::string nume;
    std::string parola;
    std::vector<Masa> mese;
    int numar_mese = 0;
    double greutate;
    double inaltime;
    int varsta;
    int index_persoana;
    static int numar_persoane;
public:
    /// Constructori
    Persoana(std::string nume_ = "", double greutate = 0, double inaltime = 0, int varsta = 0, std::string parola = "");
    Persoana(const Persoana &other);
    Persoana& operator=(const Persoana& other);

    /// Destructor virtual
    virtual ~Persoana(){}

    /// Functii normale
    void SetareParola();
    double CaloriiNecesare();
    void AdaugareMasa();
    void AfisareNumarCaloriiNecesare();
    void AfisareGreutateIdeala();
    void AfisareProcentajGrasime();
    double BMI();

    /// Geters
    int GetIndexPersoana();
    std::string GetNumePersoana();
    static int GetNumarPersoane();

    /// Functii virtuale pure
    virtual double BMR() = 0;
    virtual double ProcentajGrasime() = 0;
    virtual void AfisareTipCorp() = 0;
    virtual double GreutateIdeala() = 0;

    /// Functii prieten
    friend std::ifstream& operator>>(std::ifstream &input_file, Persoana& p);
    friend std::ofstream& operator<<(std::ofstream &output_file, Persoana& p);
    friend std::istream& operator>>(std::istream &in, Persoana& p);
    friend std::ostream& operator<<(std::ostream &out, Persoana& p);

    /// Functii statice
    static void AfisareNumarPersoane();
    static void CresteNumarPersoane();

    friend class Aplicatie;
};
int Persoana::numar_persoane = 0;

class Baiat:public Persoana {
public:
    /// Constructori / destructor
    Baiat(std::string nume = "", double greutate = 0, double inaltime = 0, int varsta = 0);
    Baiat(const Baiat &other);
    ~Baiat(){};

    /// Functii normale
    void AfisareTipCorp();
    double ProcentajGrasime();
    double BMR();
    double GreutateIdeala() ;
};

class Fata:public Persoana {
public:
    /// Constructori / destructor
    Fata(std::string nume = "", double greutate = 0, double inaltime = 0, int varsta = 0);
    Fata(const Fata &other);
    ~Fata(){}

    /// Functii normale
    void AfisareTipCorp();
    double ProcentajGrasime();
    double BMR();
    double GreutateIdeala();
};

//////////////////////////////////// FUNCTII CLASA PERSOANA ///////////////////////////////

/// Constructori

Persoana::Persoana(std::string nume_, double greutate_, double inaltime_, int varsta_, std::string parola_) : nume{nume_}, greutate(greutate_), inaltime(inaltime_), varsta(varsta_), parola(parola_) {
    index_persoana = GetNumarPersoane();
    CresteNumarPersoane();
}

Persoana::Persoana(const Persoana &other) : nume{other.nume}, greutate(other.greutate), inaltime(other.inaltime), varsta(other.varsta), parola(other.parola) {}

Persoana& Persoana::operator=(const Persoana& other) {
    nume = other.nume;
    greutate = other.greutate;
    inaltime = other.inaltime;
    varsta = other.varsta;
    index_persoana = other.index_persoana;
    parola = other.parola;
    return *this;
}

/// Operatori I/O

std::ifstream& operator>>(std::ifstream &input_file, Persoana& p) {
    input_file >> p.nume;
    input_file >> p.greutate;
    input_file >> p.inaltime;
    input_file >> p.varsta;
    input_file >> p.index_persoana;
    input_file >> p.numar_mese;
    input_file >> p.parola;

    for(int i = 0; i < p.numar_mese; i++) {
        Masa m;
        input_file >> m;
        p.mese.push_back(m);
    }
    return input_file;
}

std::ofstream& operator<<(std::ofstream &output_file, Persoana& p) {
    output_file << p.nume << " ";
    output_file << p.greutate << " ";
    output_file << p.inaltime << " ";
    output_file << p.varsta << " ";
    output_file << p.index_persoana << " ";
    output_file << p.numar_mese << " ";
    output_file << p.parola << " ";

    for(auto masa = p.mese.begin(); masa != p.mese.end(); masa++) {
        output_file << *masa << " ";
    }
    output_file << "\n";

    return output_file;
}

std::ostream& operator<<(std::ostream &out, Persoana& p) {
    out << "Nume: " << p.nume << std::endl;
    out << "Greutate: " << p.greutate << std::endl;
    out << "Inaltime: " << p.inaltime << std::endl;
    out << "Varsta: " << p.varsta << std::endl;
    out << "Index: " << p.index_persoana << std::endl;
    return out;
}

std::istream& operator>>(std::istream &in, Persoana& p) {
    std::cout << "Nume: ";
    in >> p.nume;
    std::cout << "Greutate: ";
    in >> p.greutate;
    std::cout << "Inaltime: ";
    in >> p.inaltime;
    std::cout << "Varsta: ";
    in >> p.varsta;
    p.SetareParola();
    return in;
}

/// Functii normale

double Persoana::BMI() {
    return greutate / (inaltime * inaltime);
}

void Persoana::SetareParola() {
    std::string parola, parola_aux;

    while(true) {
        std::cout << "Alegeti o parola: ";
        std::cin >> parola;
        std::cout << "Reintroduceti parola: ";
        std::cin >> parola_aux;
        if(parola == parola_aux) {
            this->parola = parola;
            return;
        }
        std::cout << "Parole diferite! Incercati din nou\n";
        std::cin.get();
    }
}

void Persoana::AdaugareMasa() {
    Masa m;
    std::cin >> m;
    mese.push_back(m);
    numar_mese++;
}

void Persoana::AfisareNumarPersoane() {
    std::cout << "Numarul persoanelor este: " << numar_persoane << std::endl;
}

void Persoana::CresteNumarPersoane() {
    numar_persoane++;
}

void Persoana::AfisareProcentajGrasime() {
    std::cout << "Procentajul dumneavostra de grasime este de " << ProcentajGrasime() << "%\n";
}

double Persoana::CaloriiNecesare() {
    int numar_antrenamente;
    std::cout << "Introduceti numarul de antrenamente din acesta saptamana: ";
    std::cin >> numar_antrenamente;

    if(numar_antrenamente <= 3)
        return BMR() * 1.375;
    if(numar_antrenamente <= 5)
        return BMR() * 1.55;
    return BMR() * 1.725;
}

void Persoana::AfisareGreutateIdeala() {
    std::cout << "Greutatea ideala este de " << GreutateIdeala() << " kg \n";
}

void Persoana::AfisareNumarCaloriiNecesare() {
    double calorii_necesare = CaloriiNecesare();
    std::cout << "Pentru a-ti mentine greutatea actuala, ai nevoie de " << calorii_necesare << " kcal pe zi \n";
    std::cout << "Pentru a slabi incet, trebuie sa consumi " << 0.9 * calorii_necesare << " kcal pe zi \n";
    std::cout << "Pentru a slabi normal, trebuie sa consumi " << 0.79 * calorii_necesare << " kcal pe zi \n";
    std::cout << "Pentru a slabi rapid, trebuie sa consumi " << 0.59 * calorii_necesare << " kcal pe zi \n";
}

/// Geters

int Persoana::GetIndexPersoana() {
    return index_persoana;
}

std::string Persoana::GetNumePersoana() {
    return nume;
}

int Persoana::GetNumarPersoane() {
    return numar_persoane;
}

//////////////////////////////////// FUNCTII CLASA BAIAT ///////////////////////////////

/// Constructori

Baiat::Baiat(std::string nume, double greutate, double inaltime, int varsta) : Persoana(nume, greutate, inaltime, varsta){}

Baiat::Baiat(const Baiat &other) : Persoana(other.nume, other.greutate, other.inaltime, other.varsta) {}


/// Functii normale

double Baiat::ProcentajGrasime() {
    return (1.2 * BMI()) + (0.23 * varsta) - 16.2;
}

void Baiat::AfisareTipCorp() {
    double procentaj_grasime = ProcentajGrasime();
    if(varsta <= 40) {
        if(procentaj_grasime < 8) {
            std::cout << "Tipul corpului: Underfat\n";
        }
        else if(procentaj_grasime < 20) {
            std::cout << "Tipul corpului: Healthy\n";
        }
        else if(procentaj_grasime < 26) {
            std::cout << "Tipul corpului: Overweight\n";
        }
        else
            std::cout << "Tipul corpului: Obese\n";

    } else if(varsta <= 60) {
        if(procentaj_grasime < 11) {
            std::cout << "Tipul corpului: Underfat\n";
        }
        else if(procentaj_grasime < 23) {
            std::cout << "Tipul corpului: Healthy\n";
        }
        else if(procentaj_grasime < 28) {
            std::cout << "Tipul corpului: Overweight\n";
        }
        else
            std::cout << "Tipul corpului: Obese\n";
    }
    else {
        if(procentaj_grasime < 13) {
            std::cout << "Tipul corpului: Underfat\n";
        }
        else if(procentaj_grasime < 26) {
            std::cout << "Tipul corpului: Healthy\n";
        }
        else if(procentaj_grasime < 31) {
            std::cout << "Tipul corpului: Overweight\n";
        }
        else
            std::cout << "Tipul corpului: Obese\n";
    }
}

double Baiat::BMR() {
    /// Mifflin-St Jeor Equation
    return 10 * greutate + 625 * inaltime - 5 * varsta + 5;
}

double Baiat::GreutateIdeala() {
    return 50 + (0.91 * (inaltime * 100 - 152.4));
}

//////////////////////////////////// FUNCTII CLASA FATA ///////////////////////////////

/// Constructori
Fata::Fata(std::string nume, double greutate, double inaltime, int varsta):Persoana(nume, greutate, inaltime, varsta) {}

Fata::Fata(const Fata &other) : Persoana(other.nume, other.greutate, other.inaltime, other.varsta) {}

/// Functii normale

double Fata::ProcentajGrasime() {
    return (1.2 * BMI()) + (0.23 * varsta) - 5.4;
}

void Fata::AfisareTipCorp() {
    double procentaj_grasime = ProcentajGrasime();
    if(varsta <= 40) {
        if(procentaj_grasime < 21) {
            std::cout << "Tipul corpului: Underfat\n";
        }
        else if(procentaj_grasime < 34) {
            std::cout << "Tipul corpului: Healthy\n";
        }
        else if(procentaj_grasime < 40) {
            std::cout << "Tipul corpului: Overweight\n";
        }
        else
            std::cout << "Tipul corpului: Obese\n";
    }
    else if(varsta <= 60) {
        if(procentaj_grasime < 23) {
            std::cout << "Tipul corpului: Underfat\n";
        }
        else if(procentaj_grasime < 36) {
            std::cout << "Tipul corpului: Healthy\n";
        }
        else if(procentaj_grasime < 41) {
            std::cout << "Tipul corpului: Overweight\n";
        }
        else
            std::cout << "Tipul corpului: Obese\n";
    }
    else {
        if(procentaj_grasime < 24) {
            std::cout << "Tipul corpului: Underfat\n";
        }
        else if(procentaj_grasime < 37) {
            std::cout << "Tipul corpului: Healthy\n";
        }
        else if(procentaj_grasime < 43) {
            std::cout << "Tipul corpului: Overweight\n";
        }
        else
            std::cout << "Tipul corpului: Obese\n";
    }
}

double Fata::BMR() {
    // Mifflin-St Jeor Equation
    return 10 * greutate + 6.25 * inaltime * 100 - 5 * varsta - 161;
}

double Fata::GreutateIdeala() {
    return 45.5 + (0.91 * (inaltime * 100 - 152.4));
}
