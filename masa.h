#include "valoare_nutritionala.h"

class Masa {
    std::string nume;
    ValoareNutritionala v;
    int cantitate;
public:
    // Masa(std::string nume_ = "", ValoareNutritionala& v_ , int cantitate = 0);
    int NumarCalorii() {
        return ((double)v.calorii / 100) * cantitate;
    }
    friend class Persoana;
    friend std::istream& operator>>(std::istream &in, Masa& m);
};

std::istream& operator>>(std::istream &in, Masa& m) {
    std::cout << "Introduceti numele mesei: ";
    in >> m.nume;
    in >>m.v;
    std::cout << "Introduceti cantitatea: ";
    in >> m.cantitate;
    return in;
}
