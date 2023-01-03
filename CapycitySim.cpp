class CapacitySim {
private:
    enum class gebaeudetyp {Leer, Haus, Hochhaus, Tinyhaus, Doppelhaushaelfte}; 
    std::vector<std::vector<gebaeudetyp>> constructionArea;
    int length, width;

public:
    CapacitySim(int length, int width) : length(length), width(width) {}

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
    
};
//TODO Übertragen der Methoden aus first_simulation_tool.cpp