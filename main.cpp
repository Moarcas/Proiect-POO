#include <iostream>
#include <string>
#include <vector>

class ValoareNutritionala {
    int calorii;
public:
    ValoareNutritionala(int calorii_) : calorii{calorii_} {
        std::cout << "Constructor de initializare ValoareNutritionala\n";
    }
    ValoareNutritionala(const ValoareNutritionala& other) : calorii{other.calorii} {
        std::cout << "Constructor de copiere ValoareNutritionala\n";
    }
    // ValoareNutritionala(ValoareNutritionala&& other) : calorii{std::move(other.calorii)} {
    //     std::cout << "Constructor de mutare ValoareNutritionala\n";
    // }
    ValoareNutritionala& operator=(const ValoareNutritionala &other) {
        calorii = other.calorii;
        return *this;
    }

    ~ValoareNutritionala() {}

    friend std::ostream& operator<<(std::ostream&os, const ValoareNutritionala& v) {
        os << v.calorii << '\n';
        return os;
    }

    ValoareNutritionala operator+=(int);
};

ValoareNutritionala ValoareNutritionala::operator+=(int cal) {
    calorii += cal;
    return *this;
}

class Masa {
    std::string nume;
    ValoareNutritionala v;
public:
    Masa(const std::string& nume_, const ValoareNutritionala& v_) : nume{nume_}, v{v_} {
        std::cout << "Constructor de initializare Masa\n";
    }

    Masa(const Masa& other, const ValoareNutritionala& v_) : nume{other.nume}, v{v_} {
        std::cout << "Constructor de copiere Masa\n";
    }

    Masa& operator=(const Masa &other) {
        nume = other.nume;
        v = other.v;
        std::cout << "operator= copiere Masa\n";
        return *this;
    }

    ~Masa() {
        std::cout << "Destructor Masa\n";
    }

    friend std::ostream& operator<<(std::ostream&os, const Masa& m) {
        os << m.nume << m.v << '\n';
        return os;
    }
};

class Persoana {
    std::string nume;
    std::vector<Masa> m;
    double inaltime, greutate;
    //int calorii_arse, calorii_mancare;

public:
    Persoana(const std::string& nume_, const std::vector<Masa>& m_, double inaltime_, double greutate_) : nume{nume_}, m{m_}, inaltime{inaltime_}, greutate{greutate_} {
        std::cout << "Constructor de initializare Persoana\n";
    }

    Persoana(const std::string& nume_,  double inaltime_, double greutate_) : nume{nume_}, inaltime{inaltime_}, greutate{greutate_} {
        std::cout << "Constructor de initializare Persoana\n";
    }

    Persoana(const Persoana &other) : nume{other.nume}, m{other.m}, inaltime{other.inaltime}, greutate{other.greutate} {
        std::cout << "Constructor de copiere Persoana\n";
    }

    Persoana& operator=(const Persoana& other) {
        nume = other.nume;
        m = other.m;
        inaltime = other.inaltime;
        greutate = other.greutate;

        std::cout << "operator= copiere Persoana\n";

        return *this;
    }

    ~Persoana() {
        std::cout << "Destructor Persoana\n";
    }

    friend std::ostream& operator<<(std::ostream&os, const Persoana& p) {
        os << p.nume << '\n';
        return os;
    }

    int operator==(Persoana other) {
        if(this->nume == other.nume)
            return 1;
        return 0;
    }

    double BMI(double inaltime, double greutate) {
        return greutate / (inaltime * inaltime);
    }

    void AfisareTipCorp() {
        double bmi = BMI(inaltime, greutate);
        if(bmi > 25)
            std::cout << nume << "'s Body Mass Index is " << bmi << ". This is considered overweight.\n";
        else
            if(bmi < 18.5)
                std::cout << nume << "'s Body Mass Index is " << bmi << ". This is considered underweight.\n";
            else
                std::cout << nume << "'s Body Mass Index is " << bmi << ". This is considered normal.\n";
    }
};

// class Exercitiu {
//     std::string nume;
//     int calorii_arse;
// public:
//
// };


int main() {
    Persoana p{"Cosmin", 1.68, 80};
    p.AfisareTipCorp();
    return 0;
}
