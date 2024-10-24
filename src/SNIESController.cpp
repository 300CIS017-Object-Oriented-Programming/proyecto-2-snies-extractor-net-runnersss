#include "SNIESController.h"

using namespace std;

SNIESController::SNIESController()
{
    gestorCsvObj = new GestorCsv();
    gestorTxtObj = new EscrituraTxt();
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

map<std::string, UnionDatos *> SNIESController::busquedaPalabraClave(std::string &palabraClave)
{
    map<std::string, UnionDatos *> mapDatosConpalabraclave;
    map<std::string, UnionDatos *>::iterator itMapUnion;
    ProgramaAcademico *programa;
    DatosInstitucion *institucion;

    for (itMapUnion = unificacion.begin(); itMapUnion != unificacion.end(); itMapUnion++)
    {
        programa = itMapUnion->second->getPrograma();
        institucion = itMapUnion->second->getInstitucion();
        if (programa->getCodigoSniesDelPrograma() == palabraClave ||
            programa->getProgramaAcademico() == palabraClave ||
            programa->getIdNivelAcademico() == palabraClave ||
            programa->getNivelAcademico() == palabraClave ||
            programa->getIdNivelDeFormacion() == palabraClave ||
            programa->getNivelDeFormacion() == palabraClave ||
            programa->getIdMetodologia() == palabraClave ||
            programa->getMetodologia() == palabraClave ||
            programa->getIdArea() == palabraClave ||
            programa->getAreaDeConocimiento() == palabraClave ||
            programa->getIdNucleo() == palabraClave ||
            programa->getNucleoBasicoDelConocimientoNbc() == palabraClave ||
            programa->getIdCineCampoAmplio() == palabraClave ||
            programa->getDescCineCampoAmplio() == palabraClave ||
            programa->getIdCineCampoEspecifico() == palabraClave ||
            programa->getDescCineCampoEspecifico() == palabraClave ||
            programa->getIdCineCodigoDetallado() == palabraClave ||
            programa->getDescCineCodigoDetallado() == palabraClave ||
            programa->getCodigoDelDepartamentoPrograma() == palabraClave ||
            programa->getDepartamentoDeOfertaDelPrograma() == palabraClave ||
            programa->getCodigoDelMunicipioPrograma() == palabraClave ||
            programa->getMunicipioDeOfertaDelPrograma() == palabraClave ||

            institucion->getCodigoDeLaInstitucion() == palabraClave ||
            institucion->getIesPadre() == palabraClave ||
            institucion->getInstitucionDeEducacionSuperiorIes() == palabraClave ||
            institucion->getPrincipalOSeccional() == palabraClave ||
            institucion->getIdSectorIes() == palabraClave ||
            institucion->getSectorIes() == palabraClave ||
            institucion->getIdCaracter() == palabraClave ||
            institucion->getCaracterIes() == palabraClave ||
            institucion->getCodigoDelDepartamentoIes() == palabraClave ||
            institucion->getDepartamentoDeDomicilioDeLaIes() == palabraClave ||
            institucion->getCodigoDelMunicipioIes() == palabraClave ||
            institucion->getMunicipioDeDomicilioDeLaIes() == palabraClave)

        {
            mapDatosConpalabraclave[itMapUnion->first] = itMapUnion->second;
        }
    }
    return mapDatosConpalabraclave;
}

// // Mantenimiento: El nombre de esta función es confuso.
// void SNIESController::buscarProgramas(bool flag, string &palabraClave, int idComparacion)
// {
//     GestorCsv *gestorCsv = new GestorCsv();
//     GestorJson *gestorJson = new GestorJson();
//     GestorTxt *gestorTxt = new GestorTxt();
//     vector<GestorBase*> gestores;
//     gestores.push_back(gestorCsv);
//     gestores.push_back(gestorJson);
//     gestores.push_back(gestorTxt);
//     int archivoCreacionElegido;
//     list<ProgramaAcademico *> listaProgramas;
//     for (map<int, ProgramaAcademico *>::iterator it = programasAcademicos.begin(); it != programasAcademicos.end(); ++it)
//     {
//         ProgramaAcademico *programa = it->second;
//         string nombre = programa->getProgramaAcademico();
//         int id = programa->getIdNivelDeFormacion();
//         if (nombre.find(palabraClave) != string::npos && id == idComparacion)
//         {
//             listaProgramas.push_back(programa);
//             // codigo SNIES, nombre del programa, codigo de la institucion, nombre de la institucion y metodología
//             cout << programa->getCodigoSniesDelPrograma() << ";" << programa->getProgramaAcademico() << ";" << programa->getCodigoDeLaInstitucion() << ";" << programa->getInstitucionDeEducacionSuperiorIes() << ";" << programa->getMetodologia() << endl;
//         }
//     }

//     if (flag)
//     {
//         bool creado;
//         cout << "Si desea crear un archivo .csv seleccione [0]" << endl;
//         cout << "Si desea crear un archivos .json seleccione [1]" << endl;
//         cout << "Si desea crear un archivo .txt seleccione [2]" << endl;
//         cin >> archivoCreacionElegido;
//         creado = gestores[archivoCreacionElegido]->crearArchivo(rutaOutput, programasAcademicos, etiquetasColumnas);
//     }
// }

// // Mantenimiento y Estructura: Esta función tiene una complejidad altísima, se puede mejorar y reducir.
// void SNIESController::calcularDatosExtra(bool flag)
// {
//     GestorCsv *gestorCsv = new GestorCsv();
//     GestorJson *gestorJson = new GestorJson();
//     GestorTxt *gestorTxt = new GestorTxt();
//     vector<GestorBase*> gestores;
//     gestores.push_back(gestorCsv);
//     gestores.push_back(gestorJson);
//     gestores.push_back(gestorTxt);
//     vector<vector<string>> matrizFinal;
//     vector<vector<string>> matrizEtiquetas1;
//     vector<vector<string>> matrizEtiquetas2;
//     vector<vector<string>> matrizEtiquetas3;
//     vector<string> etiquetas1 = {"Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual) Primer año", "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual)"};
//     matrizEtiquetas1.push_back(etiquetas1);
//     vector<string> etiquetas2 = {"Codigo Snies", "Nombre del Programa", "Nombre del Institucion", "Diferencial porcentual anual de NEOS"};
//     matrizEtiquetas2.push_back(etiquetas2);
//     vector<string> etiquetas3 = {"Codigo Snies", " Nombre del Programa sin NEOS en los ultimos 3 semestres"};
//     matrizEtiquetas3.push_back(etiquetas3);
//     vector<string> datosEtiquetas1;
//     vector<string> datosEtiquetas2;
//     int sumaPrimerAno = 0;
//     int sumaSegundoAno = 0;
//     int archivoCreacionElegido;

//     for (map<int, ProgramaAcademico *>::iterator it = programasAcademicos.begin(); it != programasAcademicos.end(); ++it)
//     {
//         int neosPrimerAno = 0;
//         int neosSegundoAno = 0;
//         int diferenciaNeos = 0;
//         ProgramaAcademico *programa = it->second;
//         int idMetodologiaBuscada = programa->getIdMetodologia();
//         if (idMetodologiaBuscada == 1 || idMetodologiaBuscada == 3)
//         {
//             for (int i = 0; i < 4; ++i)
//             {
//                 Consolidado *consolidado = programa->getConsolidado(i);
//                 int matriculados = consolidado->getMatriculados();
//                 sumaPrimerAno += matriculados;
//             }

//             for (int i = 0; i < 4; ++i)
//             {
//                 Consolidado *consolidado = programa->getConsolidado(i + 4);
//                 int matriculados = consolidado->getMatriculados();
//                 sumaSegundoAno += matriculados;
//             }
//         }
//         for (int i = 0; i < 4; ++i)
//         {
//             Consolidado *consolidado = programa->getConsolidado(i);
//             int numNeos = consolidado->getMatriculadosPrimerSemestre();
//             neosPrimerAno += numNeos;
//         }

//         for (int i = 0; i < 4; ++i)
//         {
//             Consolidado *consolidado = programa->getConsolidado(i + 4);
//             int numNeos = consolidado->getMatriculadosPrimerSemestre();
//             neosSegundoAno += numNeos;
//         }

//         if (neosPrimerAno != 0)
//         {
//             diferenciaNeos = ((neosSegundoAno - neosPrimerAno) * 100) / neosPrimerAno;
//         }
//         else
//         {
//             diferenciaNeos = 0;
//         }
//         datosEtiquetas2 = {to_string(programa->getCodigoSniesDelPrograma()), programa->getProgramaAcademico(), programa->getInstitucionDeEducacionSuperiorIes(), to_string(diferenciaNeos)};
//         matrizEtiquetas2.push_back(datosEtiquetas2);
//         int SumaNeosPrimerSemestre;
//         int SumaNeosSegundoSemestre;
//         int SumaNeosTercerSemestre;
//         int SumaNeosCuartoSemestre;
//         for (int i = 0; i < 4; ++i)
//         {
//             Consolidado *consolidados[8];
//             if (i == 0)
//             {
//                 consolidados[0] = programa->getConsolidado(i);
//                 consolidados[1] = programa->getConsolidado(i + 2);
//                 int neosHombres = consolidados[0]->getMatriculadosPrimerSemestre();
//                 int neosMujeres = consolidados[1]->getMatriculadosPrimerSemestre();
//                 SumaNeosPrimerSemestre = neosHombres + neosMujeres;
//             }
//             else if (i == 1)
//             {
//                 consolidados[2] = programa->getConsolidado(i);
//                 consolidados[3] = programa->getConsolidado(i + 2);
//                 int neosHombres = consolidados[2]->getMatriculadosPrimerSemestre();
//                 int neosMujeres = consolidados[3]->getMatriculadosPrimerSemestre();
//                 SumaNeosSegundoSemestre = neosHombres + neosMujeres;
//             }
//             else if (i == 2)
//             {
//                 consolidados[4] = programa->getConsolidado(i + 2);
//                 consolidados[5] = programa->getConsolidado(i + 4);
//                 int neosHombres = consolidados[4]->getMatriculadosPrimerSemestre();
//                 int neosMujeres = consolidados[5]->getMatriculadosPrimerSemestre();
//                 SumaNeosTercerSemestre = neosHombres + neosMujeres;
//             }
//             else if (i == 3)
//             {
//                 consolidados[6] = programa->getConsolidado(i + 2);
//                 consolidados[7] = programa->getConsolidado(i + 4);
//                 int neosHombres = consolidados[6]->getMatriculadosPrimerSemestre();
//                 int neosMujeres = consolidados[7]->getMatriculadosPrimerSemestre();
//                 SumaNeosCuartoSemestre = neosHombres + neosMujeres;
//             }
//         }

//         if ((SumaNeosPrimerSemestre == 0 && SumaNeosSegundoSemestre == 0 && SumaNeosTercerSemestre == 0) || (SumaNeosSegundoSemestre == 0 && SumaNeosTercerSemestre == 0 && SumaNeosCuartoSemestre == 0))
//         {
//             etiquetas3 = {to_string(programa->getCodigoSniesDelPrograma()),
//                           programa->getProgramaAcademico()};
//         }
//     }
//     etiquetas1 = {to_string(sumaPrimerAno), to_string(sumaSegundoAno)};
//     matrizEtiquetas1.push_back(etiquetas1);
//     matrizFinal.insert(matrizFinal.end(), matrizEtiquetas1.begin(), matrizEtiquetas1.end());
//     matrizFinal.insert(matrizFinal.end(), matrizEtiquetas2.begin(), matrizEtiquetas2.end());
//     matrizFinal.insert(matrizFinal.end(), matrizEtiquetas3.begin(), matrizEtiquetas3.end());

//     for (const auto &fila : matrizFinal)
//     {
//         for (size_t i = 0; i < fila.size(); ++i)
//         {
//             cout << fila[i];
//             if (i < fila.size() - 1)
//             {
//                 cout << ";";
//             }
//         }
//         cout << endl;
//     }

//     if (flag)
//     {
//         bool creado;
//         cout << "Si desea crear un archivo .csv seleccione [0]" << endl;
//         cout << "Si desea crear un archivos .json seleccione [1]" << endl;
//         cout << "Si desea crear un archivo .txt seleccione [2]" << endl;
//         cin >> archivoCreacionElegido;
//         creado = gestores[archivoCreacionElegido]->crearArchivo(rutaOutput, programasAcademicos, etiquetasColumnas);
//     }
// }