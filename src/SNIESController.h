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
    map<string, DatosInstitucion *> datosInstituciones;
    map<string, map<string, Consolidado *>> listaConsolidados;
    map<std::string, UnionDatos *> unificacion;
    GestorCsv *gestorCsvObj;
    vector<string> etiquetasColumnas;
    string rutaOutput;

public:
    SNIESController();
    ~SNIESController();
    void unificacionDatos();
    void determinarObjetosDatos(string &anio1);
    void determinarObjetosConsolidados(string &anio1);
    std::vector<std::vector<std::string>> asignarAdmitidos(int anio1);
    std::vector<std::vector<std::string>> asignarInscritos(int anio);
    std::vector<std::vector<std::string>> asignarMatriculados(int anio);
    std::vector<std::vector<std::string>> asignarMatriculadosPrimerSemestre(int anio);
    std::vector<std::vector<std::string>> asignarGraduados(int anio);
    std::unordered_map<std::string, int> nombresEncabezados(std::vector<std::vector<std::string>> &datos);
    std::string normalizarCodigo(const string &primerComponente, const string &segundoComponente, const string &separador);

    map<std::string, pair<int, int>> diferenciaPorcentualAnual();
    int formulaPorcentual(int totalAnio1, int totalAnio2);
    map<std::string, std::string> sinMatriculasNuevas();
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, string &, int);
};

#endif