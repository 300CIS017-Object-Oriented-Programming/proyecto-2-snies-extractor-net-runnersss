#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <string>
#include <map>
#include "Archivo.h"
#include "ArchivoCSV.h"
#include "ArchivoTXT.h"
#include "ProgramaAcademico.h"

// Clase que selecciona el tipo de archivo
class GestorArchivos
{
public:
    void crearArchivo(const std::string &formato, const std::string &ruta, multimap<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas);
};

#endif
