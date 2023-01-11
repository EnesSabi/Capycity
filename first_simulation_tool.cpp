#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>

//TODO optimizing -> check if Enum exists or usage of default enum
//Enum deklarieren
enum class Option {SetBuilding, ClearArea, PrintPlan, PrintCost, Quit};

//forward deklaration
class CapycitySim;
class Malzeme;
class Bina;
class Wasserkraftwerk;
class Windkraftwerk;
class Solarpanele;
class Leer;

//Globale Variablen
int length, width;
std::vector<Malzeme> mat;
Bina buildArr[4] = {NULL, NULL, NULL, NULL};
std::map<Bina, std::vector<Malzeme>> gMap; //Key = Gebaeudeklasse; Value = Materialienvektor

//Klassen
class CapycitySim {
    private:
        enum gebaeudetyp {Leer, Wasserkraftwerk, Windkraftwerk, Solarpanele};
        std::vector<std::vector<gebaeudetyp>> constructionArea;
        int length, width;
        std::map<std::string, gebaeudetyp> stringToGeb;
        std::map<gebaeudetyp, std::string> gebToString;
        std::map<gebaeudetyp, Bina*> gebToBina;
    public:
    CapycitySim(int length, int width) : length(length), width(width) {
        constructionArea = std::vector<std::vector<gebaeudetyp>>(length, std::vector<gebaeudetyp>(width));
        // Initialisieren der Maps
        stringToGeb["Leer"] = gebaeudetyp::Leer;
        stringToGeb["Wasserkraftwerk"] = gebaeudetyp::Wasserkraftwerk;
        stringToGeb["Windkraftwerk"] = gebaeudetyp::Windkraftwerk;
        stringToGeb["Solarpanele"] = gebaeudetyp::Solarpanele;

        gebToString[gebaeudetyp::Leer] = "Leer";
        gebToString[gebaeudetyp::Wasserkraftwerk] = "Wasserkraftwerk";
        gebToString[gebaeudetyp::Windkraftwerk] = "Windkraftwerk";
        gebToString[gebaeudetyp::Solarpanele] = "Solarpanele";

        gebToString[gebaeudetyp::Leer] = Leer();
        gebToString[gebaeudetyp::Wasserkraftwerk] = &wak;
        gebToString[gebaeudetyp::Windkraftwerk] = &wik;
        gebToString[gebaeudetyp::Solarpanele] = &sp;
    }

    bool check(int x, int y, int exLength, int exWidth) {
        if (x + exLength > length || y + exWidth > width) {
            return false;
        }
        int free_cells = 0;
        for (int i = x; i < x + exLength; ++i) {
            for (int j = y; j < y + exWidth; ++j) {
                if (constructionArea[i][j] == gebaeudetyp::Leer) {
                    ++free_cells;
                }
            }
        }
        return free_cells == exLength *exWidth;
    }
    //string to gebaeudetyp
    gebaeudetyp strToGeb(const std::string &art) {
        auto it = stringToGeb.find(art);
        if (it != stringToGeb.end()) {
            return it->second;
        } else {
            // Keine passende Art gefunden
            return gebaeudetyp::Leer;
        }
    }
    std::string gebToStr(gebaeudetyp typ) {
        auto it = gebToString.find(typ);
        if (it != gebToString.end()) {
            return it->second;
        } else {
            return "Unknow";
        }
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
            gebaeudetyp gt = strToGeb(art);
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
    constructionArea[x][y] = gebaeudetyp::Leer;
    }
    void printPlan() { //works fine
        //Ausgabe des 2 Dimensionalen Vektors, dafür brauche ich aber eine Überladung des <<-Operators
        for (const auto& row : constructionArea) {
            for (const auto& element : row) {
                std::cout << gebToStr(element) << " ";
            }
            std::cout << std::endl;
        }
    }
    void printCost() {
        double totalCost = 0;
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                Bina b = constructionArea[i][j];
                totalCost += costReturn(b);
            }
        }
        std::cout << "Die Gesamtkosten betragen: " << totalCost << std::endl;
    }
    int costReturn(gebaeudetyp gt) {
        Bina *b = gebToBina[gt];  // hier finde ich den key der gMap
        std::vector<Malzeme> materials = gMap.at(*b); // hier verwendet ich die key, um den vector zu bekommen
        int totalCost = 0;
        std::vector<Malzeme> materials = gMap.at(b);
        for(Malzeme m : materials) {
            totalCost += m.getFiyat;
        }
        return totalCost;
    }
};
    //Malzemeler
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
class Holz:public Malzeme {public:Holz(int menge): Malzeme("Holz", 10.0) {this->setMiktar(menge);}};
class Metall:public Malzeme {public:Metall(int menge): Malzeme("Metall", 20.0) {this->setMiktar(menge);}};
class Kunststoff:public Malzeme {public:Kunststoff(int menge): Malzeme("Kunststoff", 5.0){this->setMiktar(menge);}};
    //Binalar
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
        //Operatorüberladung
        bool operator<(const Bina& other) const {return this->fiyat < other.fiyat;}
        bool operator==(const Bina& other) const {return this->label == other.label;}
};
class Wasserkraftwerk:public Bina {public: Wasserkraftwerk():Bina(1000, "Wasserkraftwerk") {}};
class Windkraftwerk:public Bina {public: Windkraftwerk():Bina(2000, "Windkraftwerk"){}};
class Solarpanele:public Bina {public: Solarpanele():Bina(500,"Solarpanele"){}};
class Leer:public Bina {public: Leer():Bina(0,"Leer"){}};

//Methoden
void Mapping() {
    // Hier müssen die Materialien für ein Feld eingetragen werden. Also wie viel Materialien braucht man für ein Feld von Wasserkraftwerk zum Beispiel;

    gMap[wak] = {Holz(5), Metall(3)};
    gMap[wik] = {Holz(2), Metall(3), Kunststoff(4)};
    gMap[sp] = {Metall(2), Kunststoff(7)};
    gMap[l] = {};
};
void Quit() {
  std::cout << "Das Programm wird nun beendet. Bitte haben Sie ein wenig Geduld.";
}
void Menu(CapycitySim& sim) {
    //Anzeige eines Menues inklusive Funktionalitaet
    while(true) {
        std::cout<< std::endl << "Bitte waehlen Sie eine Option aus:" << std::endl;
        std::cout << "1. Gebaeude setzen" << std::endl;
        std::cout << "2. Bereich loeschen" << std::endl;
        std::cout << "3. Bauplan ausgeben" << std::endl;
        std::cout << "4. Kosten ausgeben" << std::endl;
        std::cout << "5. Programm beenden" << std::endl;
        std::cout << std::endl;

        // Einlesen der Auswahl
        int choice;
        std::cin >> choice;
        choice--;
        std::cout << std::endl;
        
        // Auswahloptionen ausführen
        switch (static_cast<Option>(choice)) {
            case Option::SetBuilding:
                sim.setBuilding();
                break;
            case Option::ClearArea:
                sim.ClearArea();
                break;
            case Option::PrintPlan:
                sim.printPlan();
                break;
            case Option::PrintCost:
                sim.printCost();
                break;
            case Option::Quit:
                Quit();
                return;
                break;
            default:
                std::cout << "Ungueltige Auswahl!" << std::endl;
                break;
        }

    }
}

//main Methode
int main(int argc, char** argv) {
    // Überprüfen, ob Länge und Breite als Argumente übergeben wurden
    if (argc != 3) {
        std::cerr << "Bitte Laenge und Breite des Baubereichs als Argumente uebergeben." << std::endl << std::endl;
        return 1;
    }
    // Länge und Breite aus Argumenten entnehmen
    length = atoi(argv[1]);
    width = atoi(argv[2]);
    // Ausgabe der eingegebenen Parameter
    std::cout << "Laenge des Baubereichs: " << length << std::endl;
    std::cout << "Breite des Baubereichs: " << width << std::endl << std::endl;
    /* Erstellen des Arrays mit Parameterlängen -> da dynamisch allozierter Speicher nicht bei Compilerzeit fest steht, muss ich auf vector umsteigen.*/

    buildArr[0] = Wasserkraftwerk wak;
    buildArr[1] = Windkraftwerk wik;
    buildArr[2] = Solarpanele sp;
    buildArr[3] = Leer l;

    CapycitySim sim(length, width);
    Mapping();
    Menu(sim);
  return 0;
}