#include "GestorArchivos.h"
#include <iostream>

void GestorArchivos::crearArchivo(const std::string &formato, const std::string &ruta, multimap<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas)
{
    Archivo *archivo;
    if (formato == "CSV")
    {
        archivo = new ArchivoCSV();
    }
    else if (formato == "TXT")
    {
        archivo = new ArchivoTXT();
    }
    /*
    else if (formato == "JSON")
    {
        archivo = new ArchivoJSON();
    }
    */
    else
    {
        std::cerr << "Formato no soportado: " << formato << std::endl;
        return;
    }
    archivo->guardar(ruta, mapadeProgramasAcademicos, etiquetasColumnas);
    delete archivo;
}
