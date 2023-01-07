#ifndef CAPY_SIM_H
#define CAPY_SIM_H

// Forward-Deklarationen
class CapycitySim;
class Malzeme;
class Bina;
class Wasserkraftwerk;
class Windkraftwerk;
class Solarpanele;
class Leer;
class Holz;
class Metall;
class Kunststoff;

// Enum für Optionen
enum class Option {SetBuilding, ClearArea, PrintPlan, PrintCost, Quit};

// Globale Variablen
extern std::vector<Malzeme> mat;
extern std::map<Bina, std::vector<Malzeme>> gMap;

//Klassen
class Malzeme {
    private:
        std::string isim;
        double fiyat;
        int miktar;
    public:
        Malzeme(std::string name, double preis) : fiyat(preis), isim(name) {}
        std::string getIsim() const { return isim; }
        double getFiyat() const { return fiyat; }
        void setMiktar(int menge) { this->miktar = menge; }
        int getMiktar() const { return miktar; }
        //Operatorüberladung
        friend std::ostream& operator<<(std::ostream& os, const Malzeme& m) {return os << "Das Material " << m.getIsim() << " hat die Kosten " << m.getFiyat() << ".";}
        bool operator<=(const Malzeme& other) {return this->fiyat <= other.fiyat;}
};
class Bina {
    private:
        int fiyat;
        std::string label;
        std::vector<Malzeme*> malzemeler;
    public:
        Bina(int preis, std::string label): fiyat(preis), label(label) {};
        void addMaterial(Malzeme* mal){malzemeler.push_back(mal);}
        int getPrice() {
            int price = fiyat;
            for (auto m : malzemeler) {
                price += m->getFiyat();
            }
            return price;
            }
        std::string getLabel() {return label;}
        std::vector<Malzeme*> getMalzemeler() const { return malzemeler;}

        Bina strToBina(std::string art) {
        if (art == "Wasserkraftwerk") {
            return Wasserkraftwerk();
        } else if (art == "Windkraftwerk") {
            return Bina::Windkraftwerk;
        } else if (art == "Solarpanele") {
            return Bina::Solarpanele;
        } else {
            // Keine passende Art gefunden
            return Bina::Leer;
        }
    }
        //Operatorüberladung
        bool operator<(const Bina& other) const {return this->fiyat < other.fiyat;}
        bool operator==(const Bina& other) const {return this->fiyat == other.fiyat;}
};

//Malzemeler
class Holz:
public Malzeme {public:Holz(int menge): Malzeme("Holz", 10.0) {this->setMiktar(menge);}};
class Metall:public Malzeme {public:Metall(int menge): Malzeme("Metall", 20.0) {this->setMiktar(menge);}};
class Kunststoff:public Malzeme {public:Kunststoff(int menge): Malzeme("Kunststoff", 5.0){this->setMiktar(menge);}};

//Binalar
class Wasserkraftwerk:public Bina {public: Wasserkraftwerk():Bina(1000, "Wasserkraftwerk") {}};
class Windkraftwerk:public Bina {public: Windkraftwerk():Bina(2000, "Windkraftwerk"){}};
class Solarpanele:public Bina {public: Solarpanele():Bina(500,"Solarpanele"){}};
class Leer::public Bina {public: Leer():Bina(500,"Leer"){}};

class CapycitySim {
    private:
    //enum gebaeudetyp {Leer, Wasserkraftwerk, Windkraftwerk, Solarpanele}; 
    std::vector<std::vector<Bina>> constructionArea;
    int length, width;
    static constexpr std::array<const char*, 5> BinaStrings = { 
        //Tabelle mit lesbaren Strings für jeden Wert des Binas, diese MUSS ZWINGEND mit dem Enum aktualisiert werden! Sowohl Strings als auch die Länge
        "Leer",
        "Wasserkraftwerk",
        "Windkraftwerk",
        "Solarpanele"
    };
    public:
    CapycitySim(int length, int width) : length(length), width(width) {
        constructionArea = std::vector<std::vector<Bina>>(length, std::vector<Bina>(width));
    }

    friend std::ostream& operator<<(std::ostream& os, Bina typ) {
        // Operatorüberladung für gebaudetyp und dessen ostream
        os << BinaStrings[static_cast<std::size_t>(typ)];
        return os;
    }
    bool check(int x, int y, int exLength, int exWidth) {
    if (x + exLength > length || y + exWidth > width) {
        return false;
    }

    for (int i = x; i < x + exLength; ++i) {
        for (int j = y; j < y + exWidth; ++j) {
            if (constructionArea[i][j] != Bina::Leer) {
                return false;
            }
        }
    }
    return true;
    }
    Bina strToGeb(std::string art) { //works fine
        if (art == "Wasserkraftwerk") {
            return Bina::Wasserkraftwerk;
        } else if (art == "Windkraftwerk") {
            return Bina::Windkraftwerk;
        } else if (art == "Solarpanele") {
            return Bina::Solarpanele;
        } else {
            // Keine passende Art gefunden
            return Bina::Leer;
        }
    }
    std::string gebToStr(Bina typ) { //works fine
        return BinaStrings[static_cast<std::size_t>(typ)];
    }
    void setBuilding() { //works fine
        // wichtige Variablen deklarieren
        std::string art;
        int xPos, yPos, exLength, exWidth;

        std::cout << "Bitte Art des Gebaeudes eingeben: " << std::endl;
        std::cin >> art; //Es wird nach einen Leerzeichen gestoppt
        std::cout << "Bitte Laenge des Gebaeudes eingeben: " << std::endl;
        std::cin >> exLength;
        std::cout << "Bitte Breite des Gebaeudes eingeben: " << std::endl;
        std::cin >> exWidth;
        std::cout << "Bitte Laengen Position eingeben" << std::endl;
        std::cin >> xPos;
        std::cout << "Bitte Breiten Position eingeben" << std::endl;
        std::cin >> yPos;

        if(check(xPos, yPos, exLength, exWidth)) {
            Bina gt = strToGeb(art);
            for (int i = xPos; i < xPos + exLength; ++i) {
            for (int j = yPos; j < yPos + exWidth; ++j) {
                constructionArea[i][j] = gt;
                }
            }
            std::cout << art << " wurde in x-Position " << xPos << " mit der Laenge " << exLength << " und in y-Position " << yPos << " mit der Breite " << exWidth << " geschrieben. \n \n";
        } else {
            std::cout << "Das Feld " << xPos << " " << yPos << " ist leider schon mit einem " << gebToStr(constructionArea[xPos][yPos]) << " belegt.";
        }
    }
    void ClearArea() { //works fine
    //wichtige Variablen deklarieren
    int x, y;
    std::cout << "Bitte Laengen Position eingeben" << std::endl;
    std::cin >> x;
    std::cout << "Bitte Breiten Position eingeben" << std::endl;
    std::cin >> y;
    constructionArea[x][y] = Bina::Leer;
    }
    void printPlan() { //works fine
        //Ausgabe des 2 Dimensionalen Vektors, dafür brauche ich aber eine Überladung des <<-Operators
        for (const auto& row : constructionArea) {
            for (const auto& element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }
    void printCost() { //Not integrated with everything, but works for just one
        for (auto e : BinaStrings) {
            int prices = 0;
            std::cout << "Die Materialien kosten: " << e << std::endl;
            mat = gMap[e];
            for (auto m : mat) { prices += m.getMiktar(); }
            std::cout << prices << std::endl;
        }
    }
};

#endif // CAPY_SIM_H
