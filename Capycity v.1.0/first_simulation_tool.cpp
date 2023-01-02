#include <iostream>
#include <vector>
#include <array>
#include <string>

//TODO optimizing -> check if Enum exists or usage of default enum

//Enum Klassen
enum class gebaeudetyp {Leer, Haus, Hochhaus, Tinyhaus, Doppelhaushaelfte}; 
  //Update TO-DO gebaeudetypStrings(), strToGeb();
enum class Option {SetBuilding, ClearArea, PrintPlan, Quit};

// Globale Variablen
std::vector<std::vector<gebaeudetyp>> constructionArea;
int length, width;

const std::array<const char*, 5> gebaeudetypStrings = { 
  // Tabelle mit lesbaren Strings für jeden Wert des Enums, diese MUSS ZWINGEND mit dem Enum aktualisiert werden! Sowohl Strings als auch die Länge
  "Leer",
  "Haus",
  "Hochhaus",
  "Tinyhaus",
  "Doppelhaushaelfte"
};
std::ostream& operator<<(std::ostream& os, gebaeudetyp typ) { //works fine
  // Operator wird generell überladen, also jede Überladung wird gecastet
  //Operatorüberladung für gebaudetyp und dessen ostream
  os << gebaeudetypStrings[static_cast<std::size_t>(typ)];
  return os;
}
bool check(int x, int y, int exLength, int exWidth) { //works fine
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
void Quit() {
  std::cout << "Das Programm wird nun beendet. Bitte haben Sie ein wenig geduld.";
}
int Menu() { //works fine
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
