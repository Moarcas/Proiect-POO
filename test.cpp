#include <string>
#include <utility>
#include <iostream>

class Student {
    std::string nume;
    int an;
public:
    Student(const std::string& nume_, int an_) : nume{nume_}, an{an_} {
        std::cout << "Constr de inițializare Student\n";
    }

    Student(const Student& other) : nume{other.nume}, an{other.an} {
        std::cout << "Constr de copiere Student\n";
    }

    Student(Student&& other) : nume{std::move(other.nume)}, an{std::move(other.an)} {
        std::cout << "Constr de mutare Student\n";
    }
};

class Facultate {
    std::string nume;
    Student stud;
public:
    Facultate(const std::string& nume_, const Student& stud_) : nume{nume_}, stud{stud_} {}
    //Facultate(const std::string& nume_, Student stud_) : nume{nume_}, stud{std::move(stud_)} {}
    //Facultate(const std::string& nume_, Student&& stud_) : nume{nume_}, stud{std::move(stud_)} {}
};

int main() {
    Facultate f1{"fmi", Student{"s1", 1}};
    // Facultate f1{"fmi", {"s1", 1}}; // dacă nu avem constructorul explicit, merge și așa
}
