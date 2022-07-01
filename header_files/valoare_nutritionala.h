class ValoareNutritionala {
    int calorii;
    int grasimi;
    int glucide;
    int zahar;
    int fibre;
    int proteine;
    int sare;
public:
    ValoareNutritionala(int calorii_ = 0, int grasimi_ = 0, int glucide_ = 0, int zahar_ = 0, int fibre_ = 0, int proteine_ = 0, int sare_ = 0);
    ValoareNutritionala(const ValoareNutritionala& other);
    ~ValoareNutritionala() {}

    ValoareNutritionala& operator=(const ValoareNutritionala& other) {
        calorii = other.calorii;
        grasimi = other.grasimi;
        glucide = other.glucide;
        zahar = other.zahar;
        fibre = other.fibre;
        proteine = other.proteine;
        sare = other.sare;
        return *this;
    }

    ValoareNutritionala operator+(ValoareNutritionala& other) {
        ValoareNutritionala temp;
        temp.calorii = calorii + other.calorii;
        temp.grasimi = grasimi + other.grasimi;
        temp.glucide = glucide + other.glucide;
        temp.zahar = zahar + other.zahar;
        temp.fibre = fibre + other.fibre;
        temp.proteine = proteine + other.proteine;
        temp.sare = sare + other.sare;
        return temp;
    }

    friend std::ifstream& operator>>(std::ifstream &input_file, ValoareNutritionala& v);
    friend std::ofstream& operator<<(std::ofstream &output_file, ValoareNutritionala& v);
    friend std::istream& operator>>(std::istream &in, ValoareNutritionala& v);
    friend std::ostream& operator<<(std::ostream &out, ValoareNutritionala& v);
    friend class Masa;
};

ValoareNutritionala::ValoareNutritionala(int calorii_, int grasimi_, int glucide_, int zahar_, int fibre_, int proteine_, int sare_) : calorii{calorii_}, grasimi{grasimi_}, glucide{glucide_}, zahar{zahar_}, fibre{fibre_}, proteine{proteine_}, sare{sare_} {}

ValoareNutritionala::ValoareNutritionala(const ValoareNutritionala& other) : calorii{other.calorii}, grasimi{other.grasimi}, glucide{other.glucide}, zahar{other.zahar}, fibre{other.fibre}, proteine{other.proteine}, sare{other.sare} {}

std::ifstream& operator>>(std::ifstream &input_file, ValoareNutritionala& v) {
    input_file >> v.calorii;
    input_file >> v.grasimi;
    input_file >> v.glucide;
    input_file >> v.zahar;
    input_file >> v.fibre;
    input_file >> v.proteine;
    input_file >> v.sare;
    return input_file;
}

std::ofstream& operator<<(std::ofstream &output_file, ValoareNutritionala& v) {
    output_file << v.calorii << std::endl;
    output_file << v.grasimi << std::endl;
    output_file << v.glucide << std::endl;
    output_file << v.zahar << std::endl;
    output_file << v.fibre << std::endl;
    output_file << v.proteine << std::endl;
    output_file << v.sare << std::endl;
    return output_file;
}

std::istream& operator>>(std::istream &in, ValoareNutritionala& v) {
    std::cout << "Introduceti valorea nutritionala\n";
    std::cout << "Calorii: ";
    in >> v.calorii;
    std::cout << "Grasimi: ";
    in >> v.grasimi;
    std::cout << "Glucide: ";
    in >> v.glucide;
    std::cout << "Zahar: ";
    in >> v.zahar;
    std::cout << "Fibre: ";
    in >> v.fibre;
    std::cout << "Proteine: ";
    in >> v.proteine;
    std::cout << "Sare: ";
    in >> v.sare;
    return in;
}

std::ostream& operator<<(std::ostream &out, ValoareNutritionala& v) {
    out << "Valoarea nutritionala:\n";
    out << "Calorii: " << v.calorii << std::endl;
    out << "Grasimi: " << v.grasimi << std::endl;
    out << "Glucide: " << v.glucide << std::endl;
    out << "Zahar: " << v.zahar << std::endl;
    out << "Fibre: " << v.fibre << std::endl;
    out << "Proteine: " << v.proteine << std::endl;
    out << "Sare: " << v.sare << std::endl;
    return out;
}
