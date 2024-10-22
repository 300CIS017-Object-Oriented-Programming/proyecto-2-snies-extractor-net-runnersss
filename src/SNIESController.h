#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "GestorCsv.h"
#include "DatosInstitucion.h"
using std::multimap;
using std::string;
#include "Settings.h"

class SNIESController
{
private:
    multimap<string, ProgramaAcademico *> programasAcademicos;
    multimap<string, DatosInstitucion*> datosInstituciones;
    GestorCsv *gestorCsvObj;
    vector<string> etiquetasColumnas;
    string rutaProgramasCSV;
    string rutaAdmitidos;
    string rutaGraduados;
    string rutaInscritos;
    string rutaMatriculados;
    string rutaMatriculadosPrimerSemestre;
    string rutaOutput;
public:
    SNIESController();
    ~SNIESController();
    void determinarObjetosDatos(string &anio1);
    void determinarObjetosConsolidados(string &anio1, string &anio2);
    void procesarDatosCsv(string &, string &);
    // Mantenimiento: Este método tiene un nombre confuso.
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, string &, int);
};

#endif