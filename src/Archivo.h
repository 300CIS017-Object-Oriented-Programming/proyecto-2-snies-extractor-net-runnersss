#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <map>
#include "ProgramaAcademico.h"
#include "DatosInstitucion.h"

using namespace std;

// Clase abstracta base
class Archivo
{
public:
    virtual void guardar(const std::string &ruta, multimap<int, ProgramaAcademico *> &mapadeProgramasAcademicos, multimap<string, DatosInstitucion *> &datosInstituciones, vector<string> etiquetasColumnas) = 0;
    virtual ~Archivo() = default;
};

#endif
