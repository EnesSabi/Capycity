//STL
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>
//h-Files
#include "capy_sim.h"


//TODO optimizing -> check if Enum exists or usage of default enum
//Enum deklarieren
enum class Option {SetBuilding, ClearArea, PrintPlan, PrintCost, Quit};

//forward deklaration
class CapycitySim;
class Malzeme;
class Bina;

//Globale Variablen
int length, width;
std::vector<Malzeme> mat;
std::map<Bina, std::vector<Malzeme>> gMap; //Key = Gebaeudeklasse; Value = Materialienvektor


//Methoden
void Mapping() {
    //Materialieninput
    Wasserkraftwerk wak;
    Windkraftwerk wik;
    Solarpanele sp;
    // Hier müssen die Materialien für die 
    gMap[wak] = {Holz(5), Metall(3)};
    gMap[wik] = {Holz(2), Metall(3), Kunststoff(4)};
    gMap[sp] = {Metall(2), Kunststoff(7)};
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

    CapycitySim sim(length, width);
    Menu(sim);
  return 0;
}