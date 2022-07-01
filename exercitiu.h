#include <iostream>
#include <string>

using namespace std;

class Exercitiu {
protected:
    string nume;
    int calorii_arse;

public:
    Exercitiu(string nume_ = "", int calorii_arse_ = 0);
    Exercitiu(const Exercitiu& other);
    ~Exercitiu() {}

    Exercitiu& operator=(const Exercitiu& other) {
        nume = other.nume;
        calorii_arse = other.calorii_arse;
        return *this;
    }

    Exercitiu operator+(Exercitiu& other) {
        Exercitiu temp;
        temp.nume = nume + ", " + other.nume;
        temp.calorii_arse = calorii_arse + other.calorii_arse;
        return temp;
    }

    friend ostream& operator<<(ostream &out, Exercitiu& e);
    friend istream& operator>>(istream &in, Exercitiu& e);
};

Exercitiu::Exercitiu(string nume_, int calorii_arse_) : nume{nume_}, calorii_arse{calorii_arse_} {}
Exercitiu::Exercitiu(const Exercitiu& other) : nume{other.nume}, calorii_arse{other.calorii_arse} {}

ostream& operator<<(ostream &out, Exercitiu &e) {
    out << "Nume exercitiu: " << e.nume << '\n';
    out << "Numar calorii arse: " << e.calorii_arse << '\n';
    return out;
}

istream& operator>>(istream &in, Exercitiu &e) {
    cout << "Introduceti numele exercitiului: ";
    in >> e.nume;
    cout << "Introduceti numarul caloriilor arse: ";
    in >> e.calorii_arse;
    return in;
}
