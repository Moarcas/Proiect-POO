#include "valoare_nutritionala.h"

class Masa {
    std::string nume;
    ValoareNutritionala v;
public:
    Masa();
    Masa(std::string nume_, ValoareNutritionala& v_);
    friend class Persoana;
    friend std::ifstream& operator>>(std::ifstream &input_file, Masa& m);
    friend std::ofstream& operator<<(std::ofstream &out, Masa& m);
    friend std::istream& operator>>(std::istream &in, Masa& m);
    friend std::ostream& operator<<(std::ostream &out, Masa& m);
};

Masa::Masa() {}

Masa::Masa(std::string nume_, ValoareNutritionala &v_) : nume{nume_}, v(v_) {}

std::ifstream& operator>>(std::ifstream& input_file, Masa &m) {
    input_file >> m.nume;
    input_file >> m.v;
    return input_file;
}

std::ofstream& operator<<(std::ofstream& output_file, Masa &m) {
    output_file << m.nume << '\n';
    output_file << m.v;
    return output_file;
}

std::istream& operator>>(std::istream &in, Masa& m) {
    std::cout << "Introduceti numele mesei: ";
    in >> m.nume;
    in >> m.v;
    return in;
}

std::ostream& operator<<(std::ostream &out, Masa &m) {
    out << "Numele mancarii: " << m.nume << '\n';
    out << m.v << '\n';
    return out;
}
