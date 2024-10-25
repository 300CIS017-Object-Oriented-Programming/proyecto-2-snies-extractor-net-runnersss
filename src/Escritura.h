#ifndef ESCRITURA_H
#define ESCRITURA_H

#include <string>
#include <map>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ProgramaAcademico.h"
#include "UnionDatos.h"
#include "DatosInstitucion.h"

using namespace std;

// Clase abstracta base
class Escritura
{
public:
    virtual bool escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta) = 0;
    virtual bool escrituraNoMatriculados(map<std::string, std::string> &programasSinMatriculados) = 0;
    virtual bool escritruaPorcentajeDesencenso(map<std::string, pair<int, int>> &programaYDifirencialAnual) = 0;
    virtual ~Escritura() = default;
};

#endif