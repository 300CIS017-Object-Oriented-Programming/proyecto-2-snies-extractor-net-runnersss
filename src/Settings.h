/**
 * @file Settings.h
 * @brief Este archivo de encabezado define la clase Settings, que contiene variables de ruta de archivo constantes estáticas.
 *
 * La clase Settings se utiliza para almacenar rutas de archivos como constantes estáticas. Estas rutas están destinadas para su uso
 * en toda la aplicación, permitiendo un acceso fácil a las ubicaciones de varios archivos de entrada.
 *
 * Las siguientes constantes estáticas están definidas:
 * - ADMITIDOS_FILE_PATH: Ruta al archivo de entrada "admitidos".
 * - MATRICULADOS_FILE_PATH: Ruta al archivo de entrada "matriculados".
 * - INSCRITOS_FILE_PATH: Ruta al archivo de entrada "inscritos".
 * - PROGRAMAS_FILTRAR_FILE_PATH: Ruta al archivo de entrada "programas filtrar".
 *
 * Nota: Las constantes estáticas deben definirse fuera de la clase para asignar memoria a ellas.
 *
 *
 */


#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector> 
#include <string>
using namespace std;

class Settings
{
public:
    // En la clase Settings, las variables ADMITIDOS_FILE_PATH, MATRICULADOS_FILE_PATH y ETC se declaran como static const std::string.
    // Esto significa que son constantes de tipo string que pertenecen a la clase en lugar de a instancias individuales de la clase.
    // FIXME completar para el resto de constantes
    static string ADMITIDOS_FILE_PATH;
    static string MATRICULADOS_FILE_PATH;
    static string NEOS_FILE_PATH;
    static string INSCRITOS_FILE_PATH;
    static string PROGRAMAS_FILTRAR_FILE_PATH;
    static string BASE_PATH;
    static string DELIMITADOR;
    static string GRADUADOS_FILE_PATH;
    static std::vector<std::string> camposImportantes;
    static std::vector<std::string> camposConsolidados;
    static void setRutaBase(const string &nuevaRutaBase);
    static void setAnioProgramas(string anioProgramas);
    static void setDelimitador(const char &delimitador);

};
#endif // SETTINGS_H