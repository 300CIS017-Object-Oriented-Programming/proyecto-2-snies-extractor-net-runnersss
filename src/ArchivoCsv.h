#ifndef ARCHIVO_CSV_H
#define ARCHIVO_CSV_H

#include "Archivo.h"

// Clase para manejar archivos CSV
class ArchivoCSV : public Archivo
{
public:
    void guardar(const std::string &ruta, multimap<int, ProgramaAcademico *> &mapadeProgramasAcademicos, multimap<string, DatosInstitucion *> &datosInstituciones, vector<string> etiquetasColumnas) override;
};

#endif
