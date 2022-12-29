#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <sstream>
#include <string>

enum class gebaeudetyp {Leer, Haus, Hochhaus, Tinyhaus, Doppelhaushälfte};
enum class Option {SetBuilding, ClearArea, PrintPlan, Quit};

// Tabelle mit lesbaren Strings für jeden Wert des Enums, diese MUSS ZWINGEND mit dem Enum aktualisiert werden! Sowohl Strings als auch die Länge
const std::array<const char*, 5> gebaeudetypStrings = {
  "Leer",
  "Haus",
  "Hochhaus",
  "Tinyhaus",
  "Doppelhaushälfte"
};
// Operator wird generell überladen, also jede Überladung wird gecastet
std::ostream& operator<<(std::ostream& os, gebaeudetyp typ) {
  os << gebaeudetypStrings[static_cast<std::size_t>(typ)];
  return os;
}
//Operatorüberladung für gebaudetyp und dessen ostream

void PrintPlan(const std::vector<std::vector<gebaeudetyp>>& cA) {
    //Ausgabe des 2 Dimensionalen Vektors, dafür brauche ich aber eine Überladung des <<-Operators
    for (const auto& row : cA) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    // Überprüfen, ob Länge und Breite als Argumente übergeben wurden
    if (argc != 3) {
        std::cerr << "Bitte Laenge und Breite des Baubereichs als Argumente uebergeben." << std::endl << std::endl;
        return 1;
    }

    // Länge und Breite aus Argumenten entnehmen
    int length = atoi(argv[1]);
    int width = atoi(argv[2]);

    // Ausgabe der eingegebenen Parameter
    std::cout << "Laenge des Baubereichs: " << length << std::endl;
    std::cout << "Breite des Baubereichs: " << width << std::endl << std::endl;

    /* Erstellen des Arrays mit Parameterlängen
    -> da dynamisch allozierter Speicher nicht bei Compilerzeit fest steht, muss ich auf vector umsteigen.
    constexpr std::size_t slength = static_cast<std::size_t>(length);
    constexpr std::size_t swidth = static_cast<std::size_t>(width);
    std::array<std::array<gebaeudetyp, swidth>, slength> baubereich;
    */
    std::vector<std::vector<gebaeudetyp>> constructionArea(length, std::vector<gebaeudetyp>(width));



    //Anzeige eines Menues inklusive Funktionalitaet
    std::cout << "Bitte waehlen Sie eine Option aus:" << std::endl;
    std::cout << "1. Gebaeude setzen" << std::endl;
    std::cout << "2. Bereich loeschen" << std::endl;
    std::cout << "3. Bauplan ausgeben" << std::endl;
    std::cout << "4. Programm beenden" << std::endl;
    std::cout << std::endl;

    // Einlesen der Auswahl
    int choice;
    std::cin >> choice;
    choice--;
    // Auswahloptionen ausführen
    // wichtige Variablen deklarieren
      std::string input;
      std::string art;
      int length;
      int width;
      int xPos;
      int yPos;

    switch (static_cast<Option>(choice)) {
      case Option::SetBuilding:
        std::cout << "Bitte Art, Länge, Breite, x-Position und y-Position des Gebäudes eingeben: " << std::endl;
        std::getLine(std::cin, input);
        
        // String in fünf Teile aufteilen und in Variablen speichern
        std::stringstream ss(input);
        ss >> art >> length >> width >> xPos >> yPos;
        setBuilding();
        break;
      case Option::ClearArea:
        std::cout << "Bitte Länge und Breite des Bereichs eingeben: ";
        //clearArea();
        break;
      case Option::PrintPlan:
        PrintPlan(constructionArea);
        break;
      case Option::Quit:
        return 0;
      default:
        std::cout << "Ungueltige Auswahl!" << std::endl;
        break;
    }

  return 0;
}
