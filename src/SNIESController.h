#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "GestorCsv.h"
#include "DatosInstitucion.h"
#include "Consolidado.h"
using std::multimap;
using std::string;
using std::to_string;
#include <iostream>
#include "Settings.h"

class SNIESController
{
private:
    map<string, ProgramaAcademico *> programasAcademicos;
    map<string, DatosInstitucion*> datosInstituciones;
    map<string, Consolidado*> listaConsolidados;
    std::unordered_multimap<string, Consolidado*> consolidados;
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
    std::vector<std::vector<std::string>> asignarAdmitidos(int anio1);
    std::vector<std::vector<std::string>> asignarInscritos(int anio);
    std::vector<std::vector<std::string>> asignarMatriculados(int anio);
    std::vector<std::vector<std::string>> asignarGraduados(int anio);
    std::unordered_map<std::string, int> nombresEncabezados(std::vector<std::vector<std::string>> datos);
    // Mantenimiento: Este método tiene un nombre confuso.
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, string &, int);
};

#endif