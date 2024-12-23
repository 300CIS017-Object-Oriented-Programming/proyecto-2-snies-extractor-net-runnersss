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
#include "EscrituraTxt.h"
#include "EscrituraJson.h"
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
    EscrituraTxt *gestorTxtObj;
    EscrituraJson *gestorJsonObj;
    vector<string> etiquetasColumnas;
    string rutaOutput;
    std::vector<std::vector<std::string>> asignarAdmitidos(int anio1);
    std::vector<std::vector<std::string>> asignarInscritos(int anio);
    std::vector<std::vector<std::string>> asignarMatriculados(int anio);
    std::vector<std::vector<std::string>> asignarMatriculadosPrimerSemestre(int anio);
    std::vector<std::vector<std::string>> asignarGraduados(int anio);
    std::unordered_map<std::string, int> nombresEncabezados(std::vector<std::vector<std::string>> &datos);
    std::string normalizarCodigo(const string &primerComponente, const string &segundoComponente, const string &separador);
    std::string convertirMinusculas(const std::string &cadena);

public:
    SNIESController();
    ~SNIESController();
    void unificacionDatos();
    void determinarObjetosDatos(string &anio1);
    void determinarObjetosConsolidados(string &anio1);

    void exportarCVSDExtraSinMatricula(const map<std::string, std::string> &programasSinMatriculados);
    void exportarTXTDExtraSinMatricula(const map<std::string, std::string> &programasSinMatriculados);
    void exportarJSONDExtraSinMatricula(const map<std::string, std::string> &programasSinMatriculados);
    void exportarCVSPorcentajeAnual(const map<std::string, pair<int, int>> &programaDiferenciaPorcentual);
    void exportarTXTPorcentajeAnual(const map<std::string, pair<int, int>> &programaDiferenciaPorcentual);
    void exportarJSONPorcentajeAnual(const map<std::string, pair<int, int>> &programaDiferenciaPorcentual);
    void exportarCSV(const string &nombreArchivo);
    void exportarTXT(const string &nombreArchivo);
    void exportarJSON(const string &nombreArchivo);
    map<std::string, pair<int, int>> diferenciaPorcentualAnual();
    int formulaPorcentual(int totalAnio1, int totalAnio2);
    map<std::string, std::string> sinMatriculasNuevas();
    void busquedaPalabraClave(const string &palabraClave);
    void mostrarMapa(const map<std::string, UnionDatos *> &mapDatosConpalabraclave);
};

#endif