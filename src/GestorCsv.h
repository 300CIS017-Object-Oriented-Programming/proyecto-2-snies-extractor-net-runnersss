// After
#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include "DatosInstitucion.h"
#include "UnionDatos.h"
#include "Settings.h"
#include "EscrituraTxt.h"
#include "EscrituraJson.h"
#include <fstream>
#include <sstream>
#include <cctype>

using std::getline;
using std::list;
using std::map;
using std::string;
using std::unordered_map;
using std::vector;
using namespace std;

class GestorCsv
{
private:
    string convertirStringFormaEstandar(string &stringIn);
    Settings config;
    EscrituraTxt writeTxt;
    EscrituraJson writeJson;

public:
    GestorCsv() = default;
    // unordered_map<std::string,std::string> definirProgramas();
    std::unordered_map<std::string, int> extraerEncabezados(const string &ruta);
    std::vector<std::vector<std::string>> extraerDatos(string &ruta);
    std::unordered_map<std::string, int> extraerIndices(string &ruta, std::vector<std::string> camposImportantes);
    void eliminarIndices(std::unordered_map<std::string, int> &indices, std::vector<std::vector<std::string>> &datos);
    vector<int> leerProgramasCsv(string &ruta);
    // Mantenimiento: Se puede mejorar la firma y nombre de los metodos para que sea más descriptiva
    vector<vector<string>> leerArchivoPrimera(string &rutaBase, string &ano, vector<int> &codigosSnies);
    vector<vector<string>> leerArchivoSegunda(string &rutaBase, string &ano, vector<int> &codigosSnies);
    vector<vector<string>> leerArchivo(string &rutaBase, string &ano, vector<int> &codigosSnies, int colmunaCodigoSnies);
    bool crearArchivo(string &, map<int, ProgramaAcademico *> &, vector<string>);
    bool crearArchivoBuscados(string &, list<ProgramaAcademico *> &, vector<string>);
    bool crearArchivoExtra(string &, vector<vector<string>>);
    bool escrituraCsv(map<std::string, UnionDatos *> unificacion, string &ruta);
    string escribirDatosCsv(const UnionDatos *unionDatos);
    bool escrituraTxt(map<std::string, UnionDatos *> unificacion, string &ruta);
    string escribirDatosTxt(const UnionDatos *unionDatos);
    bool escrituraJson(map<std::string, UnionDatos *> unificacion, string &ruta);
    json convertirDatosJson(const UnionDatos *unionDatos);
    map<string, int> conseguirPosicionesColumnas(string &rutaArchivo);
    int conseguirCantColumnas(map<string, int>);
    string quitarEspacioYAgregarMayus(string cadena);
};

#endif