#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <sstream>
#include <string>

//Enum Klassen
enum class gebaeudetyp {Leer, Haus, Hochhaus, Tinyhaus, Doppelhaushaelfte}; 
  //Update TO-DO gebaeudetypStrings(), strToGeb();
enum class Option {SetBuilding, ClearArea, PrintPlan, Quit};

// Globale Variablen
std::vector<std::vector<gebaeudetyp>> constructionArea;
int length, width;

// Tabelle mit lesbaren Strings für jeden Wert des Enums, diese MUSS ZWINGEND mit dem Enum aktualisiert werden! Sowohl Strings als auch die Länge
const std::array<const char*, 5> gebaeudetypStrings = {
  "Leer",
  "Haus",
  "Hochhaus",
  "Tinyhaus",
  "Doppelhaushaelfte"
};
// Operator wird generell überladen, also jede Überladung wird gecastet
//Operatorüberladung für gebaudetyp und dessen ostream
std::ostream& operator<<(std::ostream& os, gebaeudetyp typ) {
  os << gebaeudetypStrings[static_cast<std::size_t>(typ)];
  return os;
}

bool check(int x, int y, int xl, int yb) { //TODO 1. Limit if Object is bigger than area; 2. if condition doesn't work properly, the first value throws belegt but it's free.
  int a = xl - x;
  int b = yb - y;
  int limit_x = xl + x;
  int limit_y = yb + y;   
  bool free;
  for(int i = a; i > 0; i--) {
    for (int j = b; j > 0; i--) {
      if (constructionArea[a+i][b+j] == gebaeudetyp::Leer) {
        free = true;
      } else {
        return false;
      }
    }
  }
  return free;
}
gebaeudetyp strToGeb(std::string art) {
  if (art == "Haus") {
    return gebaeudetyp::Haus;
  } else if (art == "Hochhaus") {
    return gebaeudetyp::Hochhaus;
  } else if (art == "Tinyhaus") {
    return gebaeudetyp::Tinyhaus;
  } else if (art == "Doppelhaushaelfte") {
    return gebaeudetyp::Doppelhaushaelfte;
  } else {
    // Keine passende Art gefunden
    return gebaeudetyp::Leer;
  }
}
void setBuilding() { //TODO It doesn't set the object in the right positions --> Problem is maybe in checking, but needs to be tested;
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
  
  /*std::getline(std::cin, input);
  std::cout << input << std::endl << std::endl;
  std::stringstream ss(input);
  ss >> art >> xPos >> yPos;*/
  if(check(xPos, yPos, exLength, exWidth)) {
    int a = exLength - xPos;
    int b = exWidth - yPos;
    gebaeudetyp gt = strToGeb(art);
    for(int i = a; i > 0; i--) {
      for (int j = b; j > 0; i--) {
        constructionArea[a+i][b+j] = gt;
      }
    }
    //printf("%s wurde in Position %d %d geschrieben.", art, xPos, yPos);
  } else {
    printf("Das Feld %d %d ist leider schon belegt.", xPos, yPos);
  }
}
void ClearArea() {
  //wichtige Variablen deklarieren
  int x, y;
  std::cout << "Bitte Laengen Position eingeben" << std::endl;
  std::cin >> x;
  std::cout << "Bitte Breiten Position eingeben" << std::endl;
  std::cin >> y;
  constructionArea[x][y] = gebaeudetyp::Leer;
}
void printPlan() {
    //Ausgabe des 2 Dimensionalen Vektors, dafür brauche ich aber eine Überladung des <<-Operators
    for (const auto& row : constructionArea) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}
void Quit() {
  std::cout << "Das Programm wird nun beendet. Bitte haben Sie ein wenig geduld.";
}
int Menu() {
  //entweder rekursion oder while(true)
  //Anzeige eines Menues inklusive Funktionalitaet
  while(true) {
    std::cout<< std::endl << "Bitte waehlen Sie eine Option aus:" << std::endl;
    std::cout << "1. Gebaeude setzen" << std::endl;
    std::cout << "2. Bereich loeschen" << std::endl;
    std::cout << "3. Bauplan ausgeben" << std::endl;
    std::cout << "4. Programm beenden" << std::endl;
    std::cout << std::endl;

    // Einlesen der Auswahl
    int choice;
    std::cin >> choice;
    choice--;
    std::cout << std::endl;
    // Auswahloptionen ausführen
    

    switch (static_cast<Option>(choice)) {

      case Option::SetBuilding:
        setBuilding();
        break;

      case Option::ClearArea:
        ClearArea();
        break;

      case Option::PrintPlan:
        printPlan();
        break;

      case Option::Quit:
        Quit();
        return 0;
        break;

      default:
        std::cout << "Ungueltige Auswahl!" << std::endl;
        break;
    }

  }
}

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

    constructionArea = std::vector<std::vector<gebaeudetyp>>(length, std::vector<gebaeudetyp>(width));

    Menu();
  return 0;
}
