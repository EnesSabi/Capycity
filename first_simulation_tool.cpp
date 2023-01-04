#include <iostream>
#include <vector>
#include <array>
#include <string>

//TODO optimizing -> check if Enum exists or usage of default enum
//Enum deklarieren
enum class Option {SetBuilding, ClearArea, PrintPlan, PrintCost, Quit};

//Globale Variablen
int length, width;


//forward deklaration
class CapycitySim;

//Klassen
class CapycitySim {
    private:
    enum gebaeudetyp {Leer, Wasserkraftwerk, Windkraftwerk, Solarpanele}; 
    std::vector<std::vector<gebaeudetyp>> constructionArea;
    int length, width;
    static constexpr std::array<const char*, 5> gebaeudetypStrings = { 
        //Tabelle mit lesbaren Strings für jeden Wert des Enums, diese MUSS ZWINGEND mit dem Enum aktualisiert werden! Sowohl Strings als auch die Länge
        "Leer",
        "Wasserkraftwerk",
        "Windkraftwerk",
        "Solarpanele"
    };
    public:
    CapycitySim(int length, int width) : length(length), width(width) {
        constructionArea = std::vector<std::vector<gebaeudetyp>>(length, std::vector<gebaeudetyp>(width));
    }

    friend std::ostream& operator<<(std::ostream& os, gebaeudetyp typ) {
        // Operatorüberladung für gebaudetyp und dessen ostream
        os << gebaeudetypStrings[static_cast<std::size_t>(typ)];
        return os;
    }
    bool check(int x, int y, int exLength, int exWidth) {
    if (x + exLength > length || y + exWidth > width) {
        return false;
    }

    for (int i = x; i < x + exLength; ++i) {
        for (int j = y; j < y + exWidth; ++j) {
            if (constructionArea[i][j] != gebaeudetyp::Leer) {
                return false;
            }
        }
    }
    return true;
    }
    gebaeudetyp strToGeb(std::string art) { //works fine
        if (art == "Wasserkraftwerk") {
            return gebaeudetyp::Wasserkraftwerk;
        } else if (art == "Windkraftwerk") {
            return gebaeudetyp::Windkraftwerk;
        } else if (art == "Solarpanele") {
            return gebaeudetyp::Solarpanele;
        } else {
            // Keine passende Art gefunden
            return gebaeudetyp::Leer;
        }
    }
    std::string gebToStr(gebaeudetyp typ) { //works fine
        return gebaeudetypStrings[static_cast<std::size_t>(typ)];
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
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }
    void CapycitySim::printCost() {
        std::cout << "Die Materialien aller Gebäude lauten wie folgt: " << std::endl;
        for (auto building : constructionArea) {
            building->printMaterials();
        }
    }
};
    //Malzemeler
class Malzeme {
    private:
        std::string isim;
        double fiyat;
    public:
        Malzeme(std::string name, double preis) : fiyat(preis), isim(name) {}
        std::string getIsim() const { return isim; }
        double getFiyat() const { return fiyat; }
};
class Holz:public Malzeme {public:Holz(): Malzeme("Holz", 10.0){}};
class Metall:public Malzeme {public:Metall(): Malzeme("Metall", 20.0){}};
class Kunststoff:public Malzeme {public:Kunststoff(): Malzeme("Kunststoff", 5.0){}};
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

        virtual void printMaterials() const = 0; //Funzt nicht

       
};
class Wasserkraftwerk:public Bina {public: Wasserkraftwerk():Bina(1000, "Wasserkraftwerk"){
    for (int i = 0; i < 6; i++){addMaterial(new Holz());};
    for (int i = 0; i < 2; i++){addMaterial(new Metall());};
    }
    void printMaterials() { // uebel der Muell!
        std::vector<Malzeme*> Dinge = getMalzemeler();
        for (auto m : Dinge) {
            
        }
        

    }
};
class Windkraftwerk:public Bina {public: Windkraftwerk():Bina(2000, "Windkraftwerk"){
    for (int i = 0; i < 1; i++){addMaterial(new Holz());};
    for (int i = 0; i < 8; i++){addMaterial(new Metall());};
    for (int i = 0; i < 2; i++){addMaterial(new Kunststoff());};
    }
};
class Solarpanele:public Bina {public: Solarpanele():Bina(500,"Solarpanele"){
    for (int i = 0; i < 3; i++){addMaterial(new Metall());};
    for (int i = 0; i < 5; i++){addMaterial(new Kunststoff());};
    }
};

//Methoden
void Quit() {
  std::cout << "Das Programm wird nun beendet. Bitte haben Sie ein wenig geduld.";
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

    CapycitySim sim(length, width);
    Menu(sim);
  return 0;
}