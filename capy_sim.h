#ifndef CAPY_SIM_H
#define CAPY_SIM_H

// Forward-Deklarationen
class CapycitySim;
class Malzeme;
class Bina;

// Enum für Optionen
enum class Option {SetBuilding, ClearArea, PrintPlan, PrintCost, Quit};

// Globale Variablen
extern std::vector<Malzeme> mat;
extern std::map<Bina, std::vector<Malzeme>> gMap;
