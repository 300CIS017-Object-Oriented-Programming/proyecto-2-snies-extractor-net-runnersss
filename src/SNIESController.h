#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "ProgramaAcademico.h"
#include "GestorCsv.h"
#include "DatosInstitucion.h"
#include "Consolidado.h"
#include "UnionDatos.h" 
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
    map<string, map<string, Consolidado*>> listaConsolidados;
    map<std::string, UnionDatos*> unificacion;
    GestorCsv *gestorCsvObj;
    vector<string> etiquetasColumnas;
    string rutaOutput;
public:
    SNIESController();
    ~SNIESController();
    std::pair<std::string, std::string> dividirClave(const std::string& clave);
    void unificacionDatos();
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