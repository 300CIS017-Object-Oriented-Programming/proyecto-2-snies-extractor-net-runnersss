
#include "Settings.h"
// Declaración:
// Inicialización: La inicialización de estas variables se realiza fuera de la clase.
// Esto es necesario porque las variables estáticas deben ser definidas en un solo lugar en el archivo de implementación (o en el mismo archivo, pero fuera de la clase) para que el compilador sepa cuánto espacio reservar en memoria.
string Settings::BASE_PATH = "C:/SNIES_EXTRACTOR/inputs/";
string Settings::OUTPUT_PATH = "C:/SNIES_EXTRACTOR/outputs/";
string Settings::DELIMITADOR = ";";
string Settings::PROGRAMAS_FILTRAR_FILE_PATH = "";
string Settings::ADMITIDOS_FILE_PATH = BASE_PATH + "admitidos";
string Settings::MATRICULADOS_FILE_PATH = BASE_PATH + "matriculados";
string Settings::NEOS_FILE_PATH = BASE_PATH + "matriculadosPrimerSemestre";
string Settings::INSCRITOS_FILE_PATH = BASE_PATH + "inscritos";
string Settings::GRADUADOS_FILE_PATH = BASE_PATH + "graduados";
std::vector<std::string> Settings::camposImportantes = {"CÓDIGO DE LA INSTITUCIÓN","IES_PADRE","INSTITUCIÓN DE EDUCACIÓN SUPERIOR (IES)",
"PRINCIPAL O SECCIONAL","ID SECTOR IES","SECTOR IES","ID CARACTER","CARACTER IES","CÓDIGO DEL DEPARTAMENTO (IES)","DEPARTAMENTO DE DOMICILIO DE LA IES",
"CÓDIGO DEL MUNICIPIO IES","MUNICIPIO DE DOMICILIO DE LA IES","CÓDIGO SNIES DEL PROGRAMA","PROGRAMA ACADÉMICO","ID NIVEL ACADÉMICO","NIVEL ACADÉMICO",
"ID NIVEL DE FORMACIÓN","NIVEL DE FORMACIÓN","ID METODOLOGÍA","METODOLOGÍA","ID ÁREA","ÁREA DE CONOCIMIENTO","ID NÚCLEO","NÚCLEO BÁSICO DEL CONOCIMIENTO (NBC)",
"ID CINE CAMPO AMPLIO","DESC CINE CAMPO AMPLIO","ID CINE CAMPO ESPECIFICO","DESC CINE CAMPO ESPECIFICO","ID CINE CODIGO DETALLADO","DESC CINE CODIGO DETALLADO",
"CÓDIGO DEL DEPARTAMENTO (PROGRAMA)","DEPARTAMENTO DE OFERTA DEL PROGRAMA","CÓDIGO DEL MUNICIPIO (PROGRAMA)","MUNICIPIO DE OFERTA DEL PROGRAMA"};
//Se añade el CODIGO SNIES DEL PROGRAMA y CÓDIGO DEL MUNICIPIO (PROGRAMA) en consolidados para tener una clave de referencia que una los datos con los campos importates
std::vector<std::string> Settings::camposConsolidados={"CÓDIGO SNIES DEL PROGRAMA","CÓDIGO DEL MUNICIPIO (PROGRAMA)","ID SEXO","SEXO","AÑO","SEMESTRE","ADMITIDOS","GRADUADOS","INSCRITOS","MATRICULADOS","MATRICULADOS PRIMER CURSO","PRIMER CURSO"};


void Settings::setRutaBase(const string &nuevaRutaBase)
{
    BASE_PATH = nuevaRutaBase;

    ADMITIDOS_FILE_PATH = BASE_PATH + "admitidos";
    MATRICULADOS_FILE_PATH = BASE_PATH + "matriculados";
    INSCRITOS_FILE_PATH = BASE_PATH + "inscritos";
    GRADUADOS_FILE_PATH = BASE_PATH + "graduados";
}

void Settings::setAnioProgramas(string anioProgramas)
{
    PROGRAMAS_FILTRAR_FILE_PATH = BASE_PATH + "admitidos" + anioProgramas + ".csv";
}
void Settings::setDelimitador(const char &delimitador)
{
    DELIMITADOR = delimitador;
}

string Settings::getDelimitador()
{
    return DELIMITADOR;
}
