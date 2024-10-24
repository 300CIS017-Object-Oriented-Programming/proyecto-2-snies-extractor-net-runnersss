#include "SNIESController.h"

using namespace std;

SNIESController::SNIESController()
{
    gestorCsvObj = new GestorCsv();
    gestorTxtObj = new EscrituraTxt();
    gestorJsonObj = new EscrituraJson();
}

SNIESController::~SNIESController()
{
    // for (auto &pair : programasAcademicos)
    // {
    //     ((pair).second)->~ProgramaAcademico();
    //     delete pair.second;
    // }
}

void SNIESController::unificacionDatos()
{
    for (const auto &programa : programasAcademicos)
    {
        const std::string &clave = programa.first;
        if (datosInstituciones.find(clave) != datosInstituciones.end())
        {

            UnionDatos *unionDatos = new UnionDatos();
            unionDatos->setPrograma(programa.second);
            unionDatos->setInstitucion(datosInstituciones[clave]);

            if (listaConsolidados.find(clave) != listaConsolidados.end())
            {
                std::vector<Consolidado *> consolidadosVector;

                for (const auto &par : listaConsolidados[clave])
                {
                    consolidadosVector.push_back(par.second);
                }
                unionDatos->setConsolidados(consolidadosVector);
            }

            unificacion[clave] = unionDatos;
        }
    }

}

void SNIESController::determinarObjetosDatos(string &anio1)
{
    std::string ruta = Settings::ADMITIDOS_FILE_PATH + anio1 + ".csv";
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposImportantes);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);
    gestorCsvObj->eliminarIndices(indices, datos);

    // Extrae Encabezados Para realizar parametrización de índices
    std::vector<string> encabezados = datos.at(0);
    datos.erase(datos.begin());

    for (size_t i = 0; i < encabezados.size(); ++i)
    {
        posicionesEncabezados[encabezados[i]] = static_cast<int>(i);
    }

    for (const auto &fila : datos)
    {
        DatosInstitucion *institucion = new DatosInstitucion();

        institucion->setCodigoDeLaInstitucion(fila[posicionesEncabezados["CÓDIGO DE LA INSTITUCIÓN"]]);
        institucion->setIesPadre(fila[posicionesEncabezados["IES_PADRE"]]);
        institucion->setInstitucionDeEducacionSuperiorIes(fila[posicionesEncabezados["INSTITUCIÓN DE EDUCACIÓN SUPERIOR (IES)"]]);
        institucion->setPrincipalOSeccional(fila[posicionesEncabezados["PRINCIPAL O SECCIONAL"]]);
        institucion->setIdSectorIes(fila[posicionesEncabezados["ID SECTOR IES"]]);
        institucion->setSectorIes(fila[posicionesEncabezados["SECTOR IES"]]);
        institucion->setIdCaracter(fila[posicionesEncabezados["ID CARACTER"]]);
        institucion->setCaracterIes(fila[posicionesEncabezados["CARACTER IES"]]);
        institucion->setCodigoDelDepartamentoIes(fila[posicionesEncabezados["CÓDIGO DEL DEPARTAMENTO (IES)"]]);
        institucion->setDepartamentoDeDomicilioDeLaIes(fila[posicionesEncabezados["DEPARTAMENTO DE DOMICILIO DE LA IES"]]);
        institucion->setCodigoDelMunicipioIes(fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO IES"]]);
        institucion->setMunicipioDeDomicilioDeLaIes(fila[posicionesEncabezados["MUNICIPIO DE DOMICILIO DE LA IES"]]);

        // string codigo = (fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]);
        string separador = ",";
        string codigo = normalizarCodigo((fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);
        datosInstituciones[codigo] = institucion;
    }

    for (const auto &fila : datos)
    {
        ProgramaAcademico *programa = new ProgramaAcademico();

        programa->setCodigoSniesDelPrograma(fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]]);
        programa->setProgramaAcademico(fila[posicionesEncabezados["PROGRAMA ACADÉMICO"]]);
        programa->setIdNivelAcademico(fila[posicionesEncabezados["ID NIVEL ACADÉMICO"]]);
        programa->setNivelAcademico(fila[posicionesEncabezados["NIVEL ACADÉMICO"]]);
        programa->setIdNivelDeFormacion(fila[posicionesEncabezados["ID NIVEL DE FORMACIÓN"]]);
        programa->setNivelDeFormacion(fila[posicionesEncabezados["NIVEL DE FORMACIÓN"]]);
        programa->setIdMetodologia(fila[posicionesEncabezados["ID METODOLOGÍA"]]);
        programa->setMetodologia(fila[posicionesEncabezados["METODOLOGÍA"]]);
        programa->setIdArea(fila[posicionesEncabezados["ID ÁREA"]]);
        programa->setAreaDeConocimiento(fila[posicionesEncabezados["ÁREA DE CONOCIMIENTO"]]);
        programa->setIdNucleo(fila[posicionesEncabezados["ID NÚCLEO"]]);
        programa->setNucleoBasicoDelConocimientoNbc(fila[posicionesEncabezados["NÚCLEO BÁSICO DEL CONOCIMIENTO (NBC)"]]);
        programa->setIdCineCampoAmplio(fila[posicionesEncabezados["ID CINE CAMPO AMPLIO"]]);
        programa->setDescCineCampoAmplio(fila[posicionesEncabezados["DESC CINE CAMPO ESPECIFICO"]]);
        programa->setIdCineCampoEspecifico(fila[posicionesEncabezados["ID CINE CAMPO ESPECIFICO"]]);
        programa->setDescCineCampoEspecifico(fila[posicionesEncabezados["DESC CINE CAMPO ESPECIFICO"]]);
        programa->setIdCineCodigoDetallado(fila[posicionesEncabezados["ID CINE CODIGO DETALLADO"]]);
        programa->setDescCineCodigoDetallado(fila[posicionesEncabezados["DESC CINE CODIGO DETALLADO"]]);
        programa->setCodigoDelDepartamentoPrograma(fila[posicionesEncabezados["CÓDIGO DEL DEPARTAMENTO (PROGRAMA)"]]);
        programa->setDepartamentoDeOfertaDelPrograma(fila[posicionesEncabezados["DEPARTAMENTO DE OFERTA DEL PROGRAMA"]]);
        programa->setCodigoDelMunicipioPrograma(fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]);
        programa->setMunicipioDeOfertaDelPrograma(fila[posicionesEncabezados["MUNICIPIO DE OFERTA DEL PROGRAMA"]]);

        // string codigo = (fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]);
        string separador = ",";
        string codigo = normalizarCodigo((fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);
        programasAcademicos[codigo] = programa;
    }

}
void SNIESController::determinarObjetosConsolidados(string &anio1)
{
    // Debido a inconsistencias en los archivos se opta por asignar el campo año por el valor ingresado por el usuario
    std::vector<std::vector<std::string>> admitidos = asignarAdmitidos(stoi(anio1));
    std::vector<std::vector<std::string>> inscritos = asignarInscritos(stoi(anio1));
    std::vector<std::vector<std::string>> matriculados = asignarMatriculados(stoi(anio1));
    std::vector<std::vector<std::string>> graduados = asignarGraduados(stoi(anio1));
    std::vector<std::vector<std::string>> neos = asignarMatriculadosPrimerSemestre(stoi(anio1));

    std::unordered_map<std::string, int> admitidosIndices = nombresEncabezados(admitidos);
    std::unordered_map<std::string, int> inscritosIndices = nombresEncabezados(inscritos);
    std::unordered_map<std::string, int> matriculadosIndices = nombresEncabezados(matriculados);
    std::unordered_map<std::string, int> graduadosIndices = nombresEncabezados(graduados);
    std::unordered_map<std::string, int> neosIndices = nombresEncabezados(neos);

    for (const auto &fila : inscritos)
    {
        Consolidado *consolidado = new Consolidado();
        consolidado->setIdSexo(fila[inscritosIndices["ID SEXO"]]);
        consolidado->setSexo(fila[inscritosIndices["SEXO"]]);
        consolidado->setAno(anio1);
        consolidado->setSemestre(fila[inscritosIndices["SEMESTRE"]]);
        consolidado->setInscritos(fila[inscritosIndices["INSCRITOS"]]);
        consolidado->setAdmitidos("0");
        consolidado->setMatriculados("0");
        consolidado->setGraduados("0");
        consolidado->setMatriculadosPrimerSemestre("0");

        // Separar la clave en dos partes
        string separador = ",";
        string claveExterior = normalizarCodigo((fila[inscritosIndices["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[inscritosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);

        std::string claveInterior = fila[inscritosIndices["ID SEXO"]] + "," + anio1 + "," + fila[inscritosIndices["SEMESTRE"]];

        // Almacenar en el mapa de mapas
        listaConsolidados[claveExterior][claveInterior] = consolidado;
    }

    for (const auto &fila : admitidos)
    {
        string separador = ",";
        string claveExterior = normalizarCodigo((fila[admitidosIndices["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[admitidosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);
        std::string claveInterior = fila[admitidosIndices["ID SEXO"]] + "," + anio1 + "," + fila[admitidosIndices["SEMESTRE"]];

        if (listaConsolidados.find(claveExterior) != listaConsolidados.end() &&
            listaConsolidados[claveExterior].find(claveInterior) != listaConsolidados[claveExterior].end())
        {
            listaConsolidados[claveExterior][claveInterior]->setAdmitidos(fila[admitidosIndices["ADMITIDOS"]]);
        }
    }

    for (const auto &fila : matriculados)
    {
        string separador = ",";
        string claveExterior = normalizarCodigo((fila[matriculadosIndices["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[matriculadosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);
        std::string claveInterior = fila[matriculadosIndices["ID SEXO"]] + "," + anio1 + "," + fila[matriculadosIndices["SEMESTRE"]];

        if (listaConsolidados.find(claveExterior) != listaConsolidados.end() &&
            listaConsolidados[claveExterior].find(claveInterior) != listaConsolidados[claveExterior].end())
        {
            listaConsolidados[claveExterior][claveInterior]->setMatriculados(fila[matriculadosIndices["MATRICULADOS"]]);
        }
    }

    for (const auto &fila : graduados)
    {
        string separador = ",";
        string claveExterior = normalizarCodigo((fila[graduadosIndices["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[graduadosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);
        std::string claveInterior = fila[graduadosIndices["ID SEXO"]] + "," + anio1 + "," + fila[graduadosIndices["SEMESTRE"]];

        if (listaConsolidados.find(claveExterior) != listaConsolidados.end() &&
            listaConsolidados[claveExterior].find(claveInterior) != listaConsolidados[claveExterior].end())
        {
            listaConsolidados[claveExterior][claveInterior]->setGraduados(fila[graduadosIndices["GRADUADOS"]]);
        }
    }
    for (const auto &fila : neos)
    {
        string separador = ",";
        string claveExterior = normalizarCodigo((fila[neosIndices["CÓDIGO SNIES DEL PROGRAMA"]]), (fila[neosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]), separador);
        std::string claveInterior = fila[neosIndices["ID SEXO"]] + "," + anio1 + "," + fila[neosIndices["SEMESTRE"]];

        if (listaConsolidados.find(claveExterior) != listaConsolidados.end() &&
            listaConsolidados[claveExterior].find(claveInterior) != listaConsolidados[claveExterior].end())
        {
            auto it = neosIndices.find("PRIMER CURSO");
            if (it != neosIndices.end())
            {
                listaConsolidados[claveExterior][claveInterior]->setMatriculadosPrimerSemestre(fila[neosIndices["PRIMER CURSO"]]);
            }
            else if (neosIndices.find("MATRICULADOS PRIMER CURSO") != neosIndices.end())
            {
                listaConsolidados[claveExterior][claveInterior]->setMatriculadosPrimerSemestre(fila[neosIndices["MATRICULADOS PRIMER CURSO"]]);
            }
        }
    }
}

std::string SNIESController::normalizarCodigo(const string &primerComponente, const string &segundoComponente, const string &separador)
{
    try
    {
        int sinCeroInicialPrimer = std::stoi(primerComponente);
        int sinCeroInicialSegundo = std::stoi(segundoComponente);
        std::string codigo = std::to_string(sinCeroInicialPrimer) + separador + std::to_string(sinCeroInicialSegundo);
        return codigo;
    }
    catch (const std::invalid_argument &e)
    {
        return "Sin Código SNIES";
    }
    catch (const std::out_of_range &e)
    {
        return "Sin Código SNIES";
    }
}

std::unordered_map<std::string, int> SNIESController::nombresEncabezados(std::vector<std::vector<std::string>> &datos)
{
    std::unordered_map<std::string, int> posicionesEncabezados;
    std::vector<string> encabezados = datos.at(0);
    datos.erase(datos.begin());

    for (size_t i = 0; i < encabezados.size(); ++i)
    {
        posicionesEncabezados[encabezados[i]] = static_cast<int>(i);
    }
    return posicionesEncabezados;
}
std::vector<std::vector<std::string>> SNIESController::asignarAdmitidos(int anio)
{
    std::string ruta = Settings::ADMITIDOS_FILE_PATH + std::to_string(anio) + ".csv";

    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;

    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}

std::vector<std::vector<std::string>> SNIESController::asignarInscritos(int anio)
{

    std::string ruta = Settings::INSCRITOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de inscritos
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}

std::vector<std::vector<std::string>> SNIESController::asignarMatriculados(int anio)
{

    std::string ruta = Settings::MATRICULADOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de matriculados
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}
std::vector<std::vector<std::string>> SNIESController::asignarMatriculadosPrimerSemestre(int anio)
{

    std::string ruta = Settings::NEOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de matriculados
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}
std::vector<std::vector<std::string>> SNIESController::asignarGraduados(int anio)
{

    std::string ruta = Settings::GRADUADOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de graduados
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}
void SNIESController::exportarCSV(const string & nombreArchivo){
    string ruta=Settings::OUTPUT_PATH+nombreArchivo+".csv";
    gestorCsvObj->escrituraCsv(unificacion, ruta);
}
void SNIESController::exportarTXT(const string & nombreArchivo){
    string ruta=Settings::OUTPUT_PATH+nombreArchivo+".txt";
    gestorTxtObj->escrituraDatos(unificacion, ruta);
}
void SNIESController::exportarJSON(const string & nombreArchivo){
    string ruta=Settings::OUTPUT_PATH+nombreArchivo+".txt";
    gestorJsonObj->escrituraDatos(unificacion, ruta);
}
std::map<std::string, pair<int, int>> SNIESController::diferenciaPorcentualAnual()
{
    map<std::string, pair<int, int>> programaYDifirencialAnual;
    map<std::string, UnionDatos *>::iterator itMapUnion;
    std::vector<Consolidado *> consolidadostmp;
    map<string, int> anioTotalMatriculados;
    std::string programa, anio;
    int matriculados = 0, anio1, anio2, anio3, anio12, anio23;
    for (itMapUnion = unificacion.begin(); itMapUnion != unificacion.end(); itMapUnion++)
    {
        programa = itMapUnion->second->getPrograma()->getProgramaAcademico();
        consolidadostmp = itMapUnion->second->getConsolidado();
        for (int i = 0; i != consolidadostmp.size(); i++)
        {
            anio = consolidadostmp[i]->getAno();
            matriculados = std::stoi(consolidadostmp[i]->getMatriculadosPrimerSemestre());
            anioTotalMatriculados[anio] += matriculados;
        }
        anio1 = anioTotalMatriculados["2021"];
        anio2 = anioTotalMatriculados["2022"];
        anio3 = anioTotalMatriculados["2023"];

        anio12 = formulaPorcentual(anio1, anio2);
        anio23 = formulaPorcentual(anio2, anio3);
        pair<int, int> diferenciaEnLosTresAnios(anio12, anio23);
        programaYDifirencialAnual[programa] = diferenciaEnLosTresAnios;
    }
    return programaYDifirencialAnual;
}

int SNIESController::formulaPorcentual(int totalAnio1, int totalAnio2)
{
    return (((totalAnio2 * 100) / totalAnio1) - 100);
}

map<std::string, std::string> SNIESController::sinMatriculasNuevas()
{
    map<std::string, std::string> programasSinMatriculados;
    map<std::string, UnionDatos *>::iterator itMapUnion;
    std::vector<Consolidado *> consolidadostmp;
    std::string codigoSnies, programa;
    int contador, matriculados;
    bool flag;

    for (itMapUnion = unificacion.begin(); itMapUnion != unificacion.end(); itMapUnion++)
    {
        consolidadostmp = itMapUnion->second->getConsolidado();
        contador = 0;
        flag = true;
        for (int i = 0; i != consolidadostmp.size() && flag; i++)
        {
            if (std::stoi(consolidadostmp[i]->getMatriculadosPrimerSemestre()) == 0)
            {
                contador++;
                if (contador == 3)
                {
                    programa = itMapUnion->second->getPrograma()->getProgramaAcademico();
                    codigoSnies = itMapUnion->second->getPrograma()->getCodigoSniesDelPrograma();
                    programasSinMatriculados[codigoSnies] = programa;
                    flag = false;
                }
            }
            else
            {
                contador = 0;
            }
        }
    }
    return programasSinMatriculados;
}

std::string SNIESController::convertirMinusculas(const std::string &cadena) {
    std::string minuscula = cadena;
    std::transform(minuscula.begin(), minuscula.end(), minuscula.begin(), ::tolower);
    return minuscula;
}

void SNIESController::busquedaPalabraClave(const string &palabraClave)
{
    map<std::string, UnionDatos *> mapDatosConpalabraclave;
    map<std::string, UnionDatos *>::iterator itMapUnion;
    ProgramaAcademico *programa;
    DatosInstitucion *institucion;

    for (itMapUnion = unificacion.begin(); itMapUnion != unificacion.end(); itMapUnion++)
    {
        programa = itMapUnion->second->getPrograma();
        institucion = itMapUnion->second->getInstitucion();

        // Convertir palabra clave a minúsculas
        std::string palabraClaveMinus = convertirMinusculas(palabraClave);

        // Convertir los campos a minúsculas antes de compararlos
        if (convertirMinusculas(programa->getCodigoSniesDelPrograma()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getProgramaAcademico()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdNivelAcademico()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getNivelAcademico()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdNivelDeFormacion()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getNivelDeFormacion()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdMetodologia()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getMetodologia()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdArea()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getAreaDeConocimiento()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdNucleo()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getNucleoBasicoDelConocimientoNbc()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdCineCampoAmplio()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getDescCineCampoAmplio()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdCineCampoEspecifico()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getDescCineCampoEspecifico()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getIdCineCodigoDetallado()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getDescCineCodigoDetallado()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getCodigoDelDepartamentoPrograma()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getDepartamentoDeOfertaDelPrograma()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getCodigoDelMunicipioPrograma()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(programa->getMunicipioDeOfertaDelPrograma()).find(palabraClaveMinus) != std::string::npos ||

            convertirMinusculas(institucion->getCodigoDeLaInstitucion()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getIesPadre()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getInstitucionDeEducacionSuperiorIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getPrincipalOSeccional()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getIdSectorIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getSectorIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getIdCaracter()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getCaracterIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getCodigoDelDepartamentoIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getDepartamentoDeDomicilioDeLaIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getCodigoDelMunicipioIes()).find(palabraClaveMinus) != std::string::npos ||
            convertirMinusculas(institucion->getMunicipioDeDomicilioDeLaIes()).find(palabraClaveMinus) != std::string::npos)
        {
            mapDatosConpalabraclave[itMapUnion->first] = itMapUnion->second;
        }
    }



    map<std::string, UnionDatos *>::const_iterator it;

    if (mapDatosConpalabraclave.empty())
    {
        std::cout << "No se encontraron resultados para la palabra clave." << std::endl;
        return;
    }

    for (it = mapDatosConpalabraclave.begin(); it != mapDatosConpalabraclave.end(); ++it)
    {
        std::cout << "Clave: " << it->first << std::endl;

        ProgramaAcademico *programa = it->second->getPrograma();
        DatosInstitucion *institucion = it->second->getInstitucion();

        // Mostrar datos del programa académico
        std::cout << "Programa Académico: " << programa->getProgramaAcademico() << std::endl;
        std::cout << "Nivel Académico: " << programa->getNivelAcademico() << std::endl;
        std::cout << "Nivel de Formación: " << programa->getNivelDeFormacion() << std::endl;
        std::cout << "Metodología: " << programa->getMetodologia() << std::endl;
        std::cout << "Área de Conocimiento: " << programa->getAreaDeConocimiento() << std::endl;
        std::cout << "Núcleo Básico del Conocimiento (NBC): " << programa->getNucleoBasicoDelConocimientoNbc() << std::endl;

        // Mostrar datos de la institución
        std::cout << "Código de la Institución: " << institucion->getCodigoDeLaInstitucion() << std::endl;
        std::cout << "Institución de Educación Superior (IES): " << institucion->getInstitucionDeEducacionSuperiorIes() << std::endl;
        std::cout << "Departamento de Domicilio: " << institucion->getDepartamentoDeDomicilioDeLaIes() << std::endl;
        std::cout << "Municipio de Domicilio: " << institucion->getMunicipioDeDomicilioDeLaIes() << std::endl;

        std::cout << "---------------------------------------------" << std::endl;
    }

}