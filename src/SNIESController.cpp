#include "SNIESController.h"

using namespace std;

SNIESController::SNIESController()
{
    gestorCsvObj = new GestorCsv();
}

SNIESController::~SNIESController()
{
    // for (auto &pair : programasAcademicos)
    // {
    //     ((pair).second)->~ProgramaAcademico();
    //     delete pair.second;
    // }
}

void SNIESController::determinarObjetosDatos(string &anio1){
    std::string ruta=Settings::ADMITIDOS_FILE_PATH+anio1+".csv";
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta,Settings::camposImportantes);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());  
    datos=gestorCsvObj->extraerDatos(ruta);
    gestorCsvObj->eliminarIndices(indices,datos);
    
    //Extrae Encabezados Para realizar parametrización de índices
    std::vector<string> encabezados = datos.at(0); 
    datos.erase(datos.begin()); 
    
    for (size_t i = 0; i < encabezados.size(); ++i) {
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

        string codigo = (fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]);
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

        string codigo = (fila[posicionesEncabezados["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[posicionesEncabezados["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]]);
        programasAcademicos[codigo]=programa;
    }
}
void SNIESController::determinarObjetosConsolidados(string &anio1, string &anio2){

    std::vector<std::vector<std::string>> admitidos=asignarAdmitidos(stoi(anio1));
    std::vector<std::vector<std::string>> inscritos=asignarInscritos(stoi(anio1));
    std::vector<std::vector<std::string>> matriculados=asignarMatriculados(stoi(anio1));
    std::vector<std::vector<std::string>> graduados=asignarGraduados(stoi(anio1));

    std::unordered_map<std::string, int> admitidosIndices=nombresEncabezados(admitidos);
    std::unordered_map<std::string, int> inscritosIndices=nombresEncabezados(inscritos);
    std::unordered_map<std::string, int> matriculadosIndices=nombresEncabezados(matriculados);
    std::unordered_map<std::string, int> graduadosIndices=nombresEncabezados(graduados);

    for (const auto &fila : admitidos)
    {
        Consolidado *consolidado = new Consolidado();
        consolidado->setIdSexo(fila[admitidosIndices["ID SEXO"]]);
        consolidado->setSexo(fila[admitidosIndices["SEXO"]]);
        consolidado->setAno(fila[admitidosIndices["AÑO"]]);
        consolidado->setSemestre(fila[admitidosIndices["SEMESTRE"]]);
        consolidado->setAdmitidos(fila[admitidosIndices["ADMITIDOS"]]);
        consolidado->setInscritos("0");
        consolidado->setMatriculados("0");
        consolidado->setGraduados("0");
        string codigo = (fila[admitidosIndices["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[admitidosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]])+","+(fila[admitidosIndices["ID SEXO"]])+","+(fila[admitidosIndices["AÑO"]])+","+(fila[admitidosIndices["SEMESTRE"]]);
        listaConsolidados[codigo] = consolidado;
    }

    for(const auto &fila : inscritos){ 
        string codigo = (fila[inscritosIndices["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[inscritosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]])+","+(fila[inscritosIndices["ID SEXO"]])+","+(fila[inscritosIndices["AÑO"]])+","+(fila[inscritosIndices["SEMESTRE"]]);

        if(listaConsolidados.find(codigo) != listaConsolidados.end()) {
            listaConsolidados[codigo]->setInscritos(fila[inscritosIndices["INSCRITOS"]]);
        }
    }

    for(const auto &fila : matriculados){ 
        string codigo = (fila[matriculadosIndices["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[matriculadosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]])+","+(fila[matriculadosIndices["ID SEXO"]])+","+(fila[matriculadosIndices["AÑO"]])+","+(fila[matriculadosIndices["SEMESTRE"]]);
        if(listaConsolidados.find(codigo) != listaConsolidados.end()) {
            listaConsolidados[codigo]->setMatriculados(fila[matriculadosIndices["MATRICULADOS"]]);
        }
    }

    for(const auto &fila : graduados){ 
        string codigo = (fila[graduadosIndices["CÓDIGO SNIES DEL PROGRAMA"]])+","+(fila[graduadosIndices["CÓDIGO DEL MUNICIPIO (PROGRAMA)"]])+","+(fila[graduadosIndices["ID SEXO"]])+","+(fila[graduadosIndices["AÑO"]])+","+(fila[graduadosIndices["SEMESTRE"]]);
        if(listaConsolidados.find(codigo) != listaConsolidados.end()) {
            listaConsolidados[codigo]->setGraduados(fila[graduadosIndices["GRADUADOS"]]);
        }
    }
}

std::unordered_map<std::string, int> SNIESController::nombresEncabezados(std::vector<std::vector<std::string>> datos){
    std::unordered_map<std::string, int> posicionesEncabezados;  
    std::vector<string> encabezados = datos.at(0); 
    datos.erase(datos.begin()); 

    for (size_t i = 0; i < encabezados.size(); ++i) {
        posicionesEncabezados[encabezados[i]] = static_cast<int>(i);
    }
    return posicionesEncabezados;
}
std::vector<std::vector<std::string>> SNIESController::asignarAdmitidos(int anio){
    std::string ruta = Settings::ADMITIDOS_FILE_PATH+std::to_string(anio)+".csv";

    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta,Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    
    datos=gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices,datos);

    return datos;
}

std::vector<std::vector<std::string>> SNIESController::asignarInscritos(int anio) {

    std::string ruta = Settings::INSCRITOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de inscritos
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}

std::vector<std::vector<std::string>> SNIESController::asignarMatriculados(int anio) {

    std::string ruta = Settings::MATRICULADOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de matriculados
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
}
std::vector<std::vector<std::string>> SNIESController::asignarGraduados(int anio) {

    std::string ruta = Settings::GRADUADOS_FILE_PATH + std::to_string(anio) + ".csv";

    // Extraer los índices y datos del archivo de graduados
    std::unordered_map<std::string, int> indices = gestorCsvObj->extraerIndices(ruta, Settings::camposConsolidados);
    std::vector<std::vector<std::string>> datos;
    std::unordered_map<std::string, int> posicionesEncabezados(indices.size());
    datos = gestorCsvObj->extraerDatos(ruta);

    gestorCsvObj->eliminarIndices(indices, datos);

    return datos;
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