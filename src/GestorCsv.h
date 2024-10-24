#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include "DatosInstitucion.h"
#include "UnionDatos.h"
#include "Settings.h"
#include "EscrituraTxt.h"
#include "EscrituraJson.h"
#include <fstream>
#include <sstream>
#include <cctype>

using std::getline;
using std::list;
using std::map;
using std::string;
using std::unordered_map;
using std::vector;
using namespace std;

class GestorCsv
{
private:
    Settings config;

public:
    GestorCsv() = default;
    std::unordered_map<std::string, int> extraerEncabezados(const string &ruta);
    std::vector<std::vector<std::string>> extraerDatos(string &ruta);
    std::unordered_map<std::string, int> extraerIndices(string &ruta, std::vector<std::string> camposImportantes);
    void eliminarIndices(std::unordered_map<std::string, int> &indices, std::vector<std::vector<std::string>> &datos);
    bool escrituraCsv(map<std::string, UnionDatos *> unificacion, string &ruta);
    string escribirDatosCsv(const UnionDatos *unionDatos);
};

#endif