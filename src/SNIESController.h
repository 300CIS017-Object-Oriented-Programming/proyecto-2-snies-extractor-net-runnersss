#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "GestorCsv.h"
#include "DatosInstitucion.h"
using std::map;
using std::string;
#include "Settings.h"

class SNIESController
{
private:
    map<string, ProgramaAcademico *> programasAcademicos;
    map<string, DatosInstitucion*> datosInstituciones;
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
    void procesarDatosCsv(string &, string &);
    // Mantenimiento: Este método tiene un nombre confuso.
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, string &, int);
};

#endif