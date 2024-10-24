#include "GestorCsv.h"
std::unordered_map<std::string, int> GestorCsv::extraerEncabezados(string const &ruta)
{
    std::unordered_map<std::string, int> encabezados;
    std::ifstream archivoBase(ruta, std::ios::binary);

    if (!(archivoBase.is_open()))
    {
        throw std::ios_base::failure("No se pudo abrir el archivo");
    }

    string linea;
    int indice = 0;

    std::getline(archivoBase, linea);
    std::stringstream ss(linea);
    std::string encabezado;

    while (std::getline(ss, encabezado, ';'))
    {
        encabezados[encabezado] = indice++;
    }
    archivoBase.close();

    return encabezados;
}

std::string normalizarCadena(const std::string &str)
{
    std::string resultado;
    for (char c : str)
    {
        if (std::isalnum(c))
        {                                 // Mantener solo caracteres alfanuméricos
            resultado += std::tolower(c); // Convertir a minúsculas
        }
    }
    return resultado;
}

std::unordered_map<std::string, int> GestorCsv::extraerIndices(string &ruta, std::vector<std::string> camposImportantes)
{
    std::unordered_map<std::string, int> indices;
    std::unordered_map<std::string, int> encabezados;

    encabezados = extraerEncabezados(ruta);

    for (const auto &encabezado : encabezados)
    {
        std::string encabezadoNormalizado = normalizarCadena(encabezado.first);

        auto it = std::find_if(camposImportantes.begin(), camposImportantes.end(),
                               [&encabezadoNormalizado](const std::string &campo)
                               {
                                   return normalizarCadena(campo) == encabezadoNormalizado;
                               });

        if (it == camposImportantes.end())
        {
            indices[encabezado.first] = encabezado.second;
        }
    }
    return indices;
}

std::vector<std::vector<std::string>> GestorCsv::extraerDatos(string &ruta)
{
    std::vector<std::vector<std::string>> datos;
    std::ifstream archivo(ruta);
    std::string linea;

    if (!archivo.is_open())
    {
        throw std::ios_base::failure("No se pudo abrir el archivo");
    }

    while (std::getline(archivo, linea))
    {
        std::vector<std::string> fila;
        std::stringstream sstream(linea);
        std::string valor;

        while (std::getline(sstream, valor, ';'))
        {
            fila.push_back(valor);
        }

        datos.push_back(fila);
    }

    archivo.close();
    return datos;
}

void GestorCsv::eliminarIndices(std::unordered_map<std::string, int> &indices, std::vector<std::vector<std::string>> &datos)
{

    for (auto &fila : datos)
    {

        std::vector<std::string> fila_filtrada;

        for (size_t i = 0; i < fila.size(); ++i)
        {

            bool eliminar = false;
            for (const auto &par : indices)
            {
                if (i == par.second)
                {
                    eliminar = true;
                    break;
                }
            }

            if (!eliminar)
            {
                fila_filtrada.push_back(fila[i]);
            }
        }

        fila = fila_filtrada;
    }
}

bool GestorCsv::crearArchivo(string &, map<int, ProgramaAcademico *> &, vector<string>)
{
    return true;
}
bool GestorCsv::crearArchivoBuscados(string &, list<ProgramaAcademico *> &, vector<string>)
{
    return true;
}
bool GestorCsv::crearArchivoExtra(string &, vector<vector<string>>)
{
    return true;
}

// bool GestorCsv::crearArchivo(string &ruta, map<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas)
// {
//     // Este bool nos ayudará a saber si se creo exitosamente el archivo
//     bool estadoCreacion = false;
//     string rutaCompleta = ruta + "resultados.csv";
//     ofstream archivoResultados(rutaCompleta);
//     if (archivoResultados.is_open())
//     {
//         // Imprimimos en el archivo las etiquetas (Primera fila)
//         for (int i = 0; i < etiquetasColumnas.size(); i++)
//         {
//             archivoResultados << etiquetasColumnas[i] << ";";
//         }
//         archivoResultados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

//         map<int, ProgramaAcademico *>::iterator it;
//         // Leemos todos los programas del mapa para imprimirlos en el archivo
//         for (it = mapadeProgramasAcademicos.begin(); it != mapadeProgramasAcademicos.end(); it++)
//         {
//             // Imprimimos cada uno de los 8 consolidados por programa
//             for (int i = 0; i < 8; i++)
//             {
//                 // Imprimimos toda la información base del programa academico
//                 archivoResultados << (it->second)->getCodigoDeLaInstitucion() << ";";
//                 archivoResultados << (it->second)->getIesPadre() << ";";
//                 archivoResultados << (it->second)->getInstitucionDeEducacionSuperiorIes() << ";";
//                 archivoResultados << (it->second)->getPrincipalOSeccional() << ";";
//                 archivoResultados << (it->second)->getIdSectorIes() << ";";
//                 archivoResultados << (it->second)->getSectorIes() << ";";
//                 archivoResultados << (it->second)->getIdCaracter() << ";";
//                 archivoResultados << (it->second)->getCaracterIes() << ";";
//                 archivoResultados << (it->second)->getCodigoDelDepartamentoIes() << ";";
//                 archivoResultados << (it->second)->getDepartamentoDeDomicilioDeLaIes() << ";";
//                 archivoResultados << (it->second)->getCodigoDelMunicipioIes() << ";";
//                 archivoResultados << (it->second)->getMunicipioDeDomicilioDeLaIes() << ";";
//                 archivoResultados << (it->second)->getCodigoSniesDelPrograma() << ";";
//                 archivoResultados << (it->second)->getProgramaAcademico() << ";";
//                 archivoResultados << (it->second)->getIdNivelAcademico() << ";";
//                 archivoResultados << (it->second)->getNivelAcademico() << ";";
//                 archivoResultados << (it->second)->getIdNivelDeFormacion() << ";";
//                 archivoResultados << (it->second)->getNivelDeFormacion() << ";";
//                 archivoResultados << (it->second)->getIdMetodologia() << ";";
//                 archivoResultados << (it->second)->getMetodologia() << ";";
//                 archivoResultados << (it->second)->getIdArea() << ";";
//                 archivoResultados << (it->second)->getAreaDeConocimiento() << ";";
//                 archivoResultados << (it->second)->getIdNucleo() << ";";
//                 archivoResultados << (it->second)->getNucleoBasicoDelConocimientoNbc() << ";";
//                 archivoResultados << (it->second)->getIdCineCampoAmplio() << ";";
//                 archivoResultados << (it->second)->getDescCineCampoAmplio() << ";";
//                 archivoResultados << (it->second)->getIdCineCampoEspecifico() << ";";
//                 archivoResultados << (it->second)->getDescCineCampoEspecifico() << ";";
//                 archivoResultados << (it->second)->getIdCineCodigoDetallado() << ";";
//                 archivoResultados << (it->second)->getDescCineCodigoDetallado() << ";";
//                 archivoResultados << (it->second)->getCodigoDelDepartamentoPrograma() << ";";
//                 archivoResultados << (it->second)->getDepartamentoDeOfertaDelPrograma() << ";";
//                 archivoResultados << (it->second)->getCodigoDelMunicipioPrograma() << ";";
//                 archivoResultados << (it->second)->getMunicipioDeOfertaDelPrograma() << ";";

//                 // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
//                 Consolidado *consolidadoActual = (it->second)->getConsolidado(i);
//                 archivoResultados << consolidadoActual->getIdSexo() << ";";
//                 archivoResultados << consolidadoActual->getSexo() << ";";
//                 archivoResultados << consolidadoActual->getAno() << ";";
//                 archivoResultados << consolidadoActual->getSemestre() << ";";
//                 archivoResultados << consolidadoActual->getAdmitidos() << ";";
//                 archivoResultados << consolidadoActual->getGraduados() << ";";
//                 archivoResultados << consolidadoActual->getInscritos() << ";";
//                 archivoResultados << consolidadoActual->getMatriculados() << ";";
//                 archivoResultados << consolidadoActual->getMatriculadosPrimerSemestre();
//                 // Saltamos de linea para la siguiente fila
//                 archivoResultados << endl;
//             }
//         }

//         // Cambiamos el valor del booleano si logramos llegar hasta este punto
//         estadoCreacion = true;
//         // Imprimimos ruta donde quedo el archivo
//         cout << "Archivo Creado en: " << rutaCompleta << endl;
//     }

//     archivoResultados.close();
//     return estadoCreacion;
// }

// bool GestorCsv::crearArchivoBuscados(string &ruta, list<ProgramaAcademico *> &programasBuscados, vector<string> etiquetasColumnas)
// {
//     // Este bool nos ayudará a saber si se creo exitosamente el archivo
//     bool estadoCreacion = false;
//     string rutaCompleta = ruta + "buscados.csv";
//     ofstream archivoBuscados(rutaCompleta);
//     if (archivoBuscados.is_open())
//     {

//         // Imprimimos en el archivo las etiquetas (Primera fila)
//         for (int i = 0; i < etiquetasColumnas.size(); i++)
//         {
//             archivoBuscados << etiquetasColumnas[i] << ";";
//         }
//         archivoBuscados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

//         list<ProgramaAcademico *>::iterator it;
//         // Leemos todos los programas de la lista de los programas buscados para imprimirlos
//         for (it = programasBuscados.begin(); it != programasBuscados.end(); it++)
//         {
//             // Imprimimos los 8 consolidados del programa
//             for (int i = 0; i < 8; i++)
//             {
//                 // Imprimimos la informacion base del programa
//                 archivoBuscados << (*it)->getCodigoDeLaInstitucion() << ";";
//                 archivoBuscados << (*it)->getIesPadre() << ";";
//                 archivoBuscados << (*it)->getInstitucionDeEducacionSuperiorIes() << ";";
//                 archivoBuscados << (*it)->getPrincipalOSeccional() << ";";
//                 archivoBuscados << (*it)->getIdSectorIes() << ";";
//                 archivoBuscados << (*it)->getSectorIes() << ";";
//                 archivoBuscados << (*it)->getIdCaracter() << ";";
//                 archivoBuscados << (*it)->getCaracterIes() << ";";
//                 archivoBuscados << (*it)->getCodigoDelDepartamentoIes() << ";";
//                 archivoBuscados << (*it)->getDepartamentoDeDomicilioDeLaIes() << ";";
//                 archivoBuscados << (*it)->getCodigoDelMunicipioIes() << ";";
//                 archivoBuscados << (*it)->getMunicipioDeDomicilioDeLaIes() << ";";
//                 archivoBuscados << (*it)->getCodigoSniesDelPrograma() << ";";
//                 archivoBuscados << (*it)->getProgramaAcademico() << ";";
//                 archivoBuscados << (*it)->getIdNivelAcademico() << ";";
//                 archivoBuscados << (*it)->getNivelAcademico() << ";";
//                 archivoBuscados << (*it)->getIdNivelDeFormacion() << ";";
//                 archivoBuscados << (*it)->getNivelDeFormacion() << ";";
//                 archivoBuscados << (*it)->getIdMetodologia() << ";";
//                 archivoBuscados << (*it)->getMetodologia() << ";";
//                 archivoBuscados << (*it)->getIdArea() << ";";
//                 archivoBuscados << (*it)->getAreaDeConocimiento() << ";";
//                 archivoBuscados << (*it)->getIdNucleo() << ";";
//                 archivoBuscados << (*it)->getNucleoBasicoDelConocimientoNbc() << ";";
//                 archivoBuscados << (*it)->getIdCineCampoAmplio() << ";";
//                 archivoBuscados << (*it)->getDescCineCampoAmplio() << ";";
//                 archivoBuscados << (*it)->getIdCineCampoEspecifico() << ";";
//                 archivoBuscados << (*it)->getDescCineCampoEspecifico() << ";";
//                 archivoBuscados << (*it)->getIdCineCodigoDetallado() << ";";
//                 archivoBuscados << (*it)->getDescCineCodigoDetallado() << ";";
//                 archivoBuscados << (*it)->getCodigoDelDepartamentoPrograma() << ";";
//                 archivoBuscados << (*it)->getDepartamentoDeOfertaDelPrograma() << ";";
//                 archivoBuscados << (*it)->getCodigoDelMunicipioPrograma() << ";";
//                 archivoBuscados << (*it)->getMunicipioDeOfertaDelPrograma() << ";";

//                 // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
//                 Consolidado *consolidadoActual = (*it)->getConsolidado(i);
//                 archivoBuscados << consolidadoActual->getIdSexo() << ";";
//                 archivoBuscados << consolidadoActual->getSexo() << ";";
//                 archivoBuscados << consolidadoActual->getAno() << ";";
//                 archivoBuscados << consolidadoActual->getSemestre() << ";";
//                 archivoBuscados << consolidadoActual->getAdmitidos() << ";";
//                 archivoBuscados << consolidadoActual->getGraduados() << ";";
//                 archivoBuscados << consolidadoActual->getInscritos() << ";";
//                 archivoBuscados << consolidadoActual->getMatriculados() << ";";
//                 archivoBuscados << consolidadoActual->getMatriculadosPrimerSemestre();
//                 // Saltamos de linea para la siguiente fila
//                 archivoBuscados << endl;
//             }
//         }

//         // Cambiamos el valor del booleano si logramos llegar hasta este punto
//         estadoCreacion = true;
//         // Imprimimos ruta donde quedo el archivo
//         cout << "Archivo Creado en: " << rutaCompleta << endl;
//     }

//     archivoBuscados.close();
//     return estadoCreacion;
// }

// bool GestorCsv::crearArchivoExtra(string &ruta, vector<vector<string>> datosAImprimir)
// {
//     // Este bool nos ayudará a saber si se creo el archivo exitosamente
//     bool estadoCreacion = false;
//     string rutaCompleta = ruta + "extras.csv";
//     ofstream archivoExtra(rutaCompleta);
//     if (archivoExtra.is_open())
//     {
//         // Imprimimos la matriz de datos que queremos imprimir
//         for (int i = 0; i < datosAImprimir.size(); i++)
//         {
//             // Imprimimos cada fila
//             for (int j = 0; j < datosAImprimir[i].size(); j++)
//             {
//                 // Imprimimos cada dato separado por ';'
//                 archivoExtra << datosAImprimir[i][j];
//                 if (j != (datosAImprimir[i].size() - 1))
//                 {
//                     archivoExtra << ";";
//                 }
//             }
//             // Saltamos de linea al terminar una fila
//             archivoExtra << endl;
//         }

//         // Cambiamos el valor del booleano si logramos llegar hasta este punto
//         estadoCreacion = true;
//         // Imprimimos ruta donde quedo el archivo
//         cout << "Archivo Creado en: " << rutaCompleta << endl;
//     }

//     archivoExtra.close();
//     return estadoCreacion;
// }

// map<string, int> GestorCsv::conseguirPosicionesColumnas(string &rutaArchivo) {
//     // TODO: agregar las claves sin espacio y todo en mayúsculas
//     map<string, int> mapaConPosiciones;

//     ifstream archivo(rutaArchivo);
//     // TODO: manejar la excepción. Throw a dónde? Al SNIESController?
//     if (!(archivo.is_open()))
//     {
//         cout << "Archivo " << rutaArchivo << " no se pudo abrir correctamente" << endl;
//     }
//     else {
//         string fila;
//         string dato;
//         vector<string> vectorFila;
//         stringstream streamFila;
//         int columna;

//         // Primera iteracion del ciclo para guardar las etiquetas
//         getline(archivo, fila);
//         streamFila = stringstream(fila);
//         columna = 0;
//         while ((getline(streamFila, dato, ';')))
//         {
//             dato = quitarEspacioYAgregarMayus(dato);
//             mapaConPosiciones[dato] = columna;
//             columna++;
//         }
//     }
//     archivo.close();

//     // Imprimir el mapa
//     /*
//     for (const auto& par : mapaConPosiciones) {
//         cout << "Nombre: " << par.first << ", Posicion: " << par.second << endl;
//     }
//     */

//     return mapaConPosiciones;
// }

// int GestorCsv::conseguirCantColumnas(map<string, int> mapa) {
//     int maxPosicion = 0;

//     // Recorrer el mapa y encontrar la posición más grande
//     for (const auto& par : mapa) {
//         if (par.second > maxPosicion) {
//             maxPosicion = par.second;
//         }
//     }
//     cout << "La posicion mas grande es: " << maxPosicion << endl;

//     return maxPosicion;
// }

// string GestorCsv::quitarEspacioYAgregarMayus(string cadena) {
//     std::transform(cadena.begin(), cadena.end(), cadena.begin(), ::toupper);
//     std::replace(cadena.begin(), cadena.end(), ' ', '_');

//     return cadena;
// }

// string GestorCsv::convertirStringFormaEstandar(string &stringIn) {
//     static const unordered_map<char, char> tildesMap = {
//         {'á', 'a'}, {'Á', 'a'},
//         {'é', 'e'}, {'É', 'e'},
//         {'í', 'i'}, {'Í', 'i'},
//         {'ó', 'o'}, {'Ó', 'o'},
//         {'ú', 'u'}, {'Ú', 'u'}
//     };

//     string ans;
//     for (int i = 0; i < stringIn.length(); ++i) {
//         char letra = tolower(stringIn[i]);  // Se convierte a minúscula

//         if (tildesMap.count(letra)) {
//             letra = tildesMap.at(letra);  // Se reemplaza la vocal con tilde
//         }

//         if (letra != ' ' && letra != '-') {
//             ans += letra;
//         }
//     }

//     return ans;
// }

bool GestorCsv::escrituraCsv(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    std::string texto;

    // Crear encabezado del CSV
    texto += "CodigoSnies,ProgramaAcademico,IdNivelAcademico,NivelAcademico,IdNivelFormacion,NivelFormacion,IdMetodologia,Metodologia,IdArea,AreaConocimiento,IdNucleo,NucleoBasicoConocimiento,IdCineCampoAmplio,DescCineCampoAmplio,IdCineCampoEspecifico,DescCineCampoEspecifico,IdCineCodigoDetallado,DescCineCodigoDetallado,CodigoDepartamentoPrograma,DepartamentoOfertaPrograma,CodigoMunicipio,MunicipioDeOfertaPrograma,CodigoInstitucion,IesPadre,InstitucionEducacionSuperiorIes,PrincipalOSeccional,IdSectorIes,SectorIes,IdCaracter,CaracterIes,CodigoDepartamentoIes,DepartamentoDomicilioIes,CodigoMunicipioIes,MunicipioDomicilioIes,IdSexo,Sexo,Anio,Semestre,Inscritos,Admitidos,Matriculados,MatriculadosPrimerSemestre,Graduados\n";

    // Iterar sobre los datos y escribir cada línea
    map<std::string, UnionDatos *>::iterator it;
    for (it = unificacion.begin(); it != unificacion.end(); it++)
    {
        texto += escribirDatosCsv(it->second); // Concatenamos los datos en formato CSV por cada objeto
    }

    std::ofstream archivo(ruta);

    if (!archivo.is_open())
    {
        confirmacion = false;
    }
    else
    {
        archivo << texto; // Escribimos todo el contenido en formato CSV
        archivo.close();
    }

    return confirmacion;
}

std::string GestorCsv::escribirDatosCsv(const UnionDatos *unionDatos)
{
    std::string texto;
    string delimitador = config.getDelimitador();
    ProgramaAcademico *programaActual = unionDatos->getPrograma();

    // Datos del programa académico
    texto += programaActual->getCodigoSniesDelPrograma() + delimitador;
    texto += programaActual->getProgramaAcademico() + delimitador;
    texto += (programaActual->getIdNivelAcademico()) + delimitador;
    texto += programaActual->getNivelAcademico() + delimitador;
    texto += (programaActual->getIdNivelDeFormacion()) + delimitador;
    texto += programaActual->getNivelDeFormacion() + delimitador;
    texto += (programaActual->getIdMetodologia()) + delimitador;
    texto += programaActual->getMetodologia() + delimitador;
    texto += (programaActual->getIdArea()) + delimitador;
    texto += programaActual->getAreaDeConocimiento() + delimitador;
    texto += (programaActual->getIdNucleo()) + delimitador;
    texto += programaActual->getNucleoBasicoDelConocimientoNbc() + delimitador;
    texto += (programaActual->getIdCineCampoAmplio()) + delimitador;
    texto += programaActual->getDescCineCampoAmplio() + delimitador;
    texto += (programaActual->getIdCineCampoEspecifico()) + delimitador;
    texto += programaActual->getDescCineCampoEspecifico() + delimitador;
    texto += (programaActual->getIdCineCodigoDetallado()) + delimitador;
    texto += programaActual->getDescCineCodigoDetallado() + delimitador;
    texto += programaActual->getCodigoDelDepartamentoPrograma() + delimitador;
    texto += programaActual->getDepartamentoDeOfertaDelPrograma() + delimitador;
    texto += programaActual->getCodigoDelMunicipioPrograma() + delimitador;
    texto += programaActual->getMunicipioDeOfertaDelPrograma() + delimitador;

    // Datos de la institución
    DatosInstitucion *datosInstiActuales = unionDatos->getInstitucion();
    texto += datosInstiActuales->getCodigoDeLaInstitucion() + delimitador;
    texto += datosInstiActuales->getIesPadre() + delimitador;
    texto += datosInstiActuales->getInstitucionDeEducacionSuperiorIes() + delimitador;
    texto += datosInstiActuales->getPrincipalOSeccional() + delimitador;
    texto += (datosInstiActuales->getIdSectorIes()) + delimitador;
    texto += datosInstiActuales->getSectorIes() + delimitador;
    texto += (datosInstiActuales->getIdCaracter()) + delimitador;
    texto += datosInstiActuales->getCaracterIes() + delimitador;
    texto += datosInstiActuales->getCodigoDelDepartamentoIes() + delimitador;
    texto += datosInstiActuales->getDepartamentoDeDomicilioDeLaIes() + delimitador;
    texto += datosInstiActuales->getCodigoDelMunicipioIes() + delimitador;
    texto += datosInstiActuales->getMunicipioDeDomicilioDeLaIes() + delimitador;

    // Datos de los consolidados (podría haber varios, se necesita un bucle)
    vector<Consolidado *> consolidadosActuales = unionDatos->getConsolidado();
    for (int i = 0; i < consolidadosActuales.size(); i++)
    {
        texto += (consolidadosActuales[i]->getIdSexo()) + delimitador;
        texto += consolidadosActuales[i]->getSexo() + delimitador;
        texto += (consolidadosActuales[i]->getAno()) + delimitador;
        texto += (consolidadosActuales[i]->getSemestre()) + delimitador;
        texto += (consolidadosActuales[i]->getInscritos()) + delimitador;
        texto += (consolidadosActuales[i]->getAdmitidos()) + delimitador;
        texto += (consolidadosActuales[i]->getMatriculados()) + delimitador;
        texto += (consolidadosActuales[i]->getMatriculadosPrimerSemestre()) + delimitador;
        texto += (consolidadosActuales[i]->getGraduados()) + delimitador; // Fin de la fila (nueva línea)
    }

    return texto;
}

bool GestorCsv::escrituraTxt(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    string texto;
    map<std::string, UnionDatos *>::iterator it;
    for (it = unificacion.begin(); it != unificacion.end(); it++)
    {
        texto += escribirDatosTxt(it->second);
    }

    std::ofstream archivo(ruta);

    if (!archivo.is_open())
    {
        confirmacion = false;
    }

    archivo << texto; // Aquí se supone que el contenido ha sido escrito en formato texto.
    archivo.close();

    return confirmacion;
}

string GestorCsv::escribirDatosTxt(const UnionDatos *unionDatos)
{
    string texto;
    ProgramaAcademico *programaActual = unionDatos->getPrograma();
    texto += "Programa:\n";
    texto += "  CodigoSnies: " + programaActual->getCodigoSniesDelPrograma() + "\n";
    texto += "  ProgramaAcademico: " + programaActual->getProgramaAcademico() + "\n";
    texto += "  IdNivelAcademico: " + (programaActual->getIdNivelAcademico()) + "\n";
    texto += "  NivelAcademico: " + programaActual->getNivelAcademico() + "\n";
    texto += "  IdNivelFormacion: " + (programaActual->getIdNivelDeFormacion()) + "\n";
    texto += "  NivelFormacion: " + programaActual->getNivelDeFormacion() + "\n";
    texto += "  IdMetodologia: " + (programaActual->getIdMetodologia()) + "\n";
    texto += "  Metodologia: " + programaActual->getMetodologia() + "\n";
    texto += "  IdArea: " + (programaActual->getIdArea()) + "\n";
    texto += "  AreaConocimiento: " + programaActual->getAreaDeConocimiento() + "\n";
    texto += "  IdNucleo: " + (programaActual->getIdNucleo()) + "\n";
    texto += "  NucleoBasicoConocimiento: " + programaActual->getNucleoBasicoDelConocimientoNbc() + "\n";
    texto += "  IdCineCampoAmplio: " + (programaActual->getIdCineCampoAmplio()) + "\n";
    texto += "  DescCineCampoAmplio: " + programaActual->getDescCineCampoAmplio() + "\n";
    texto += "  IdCineCampoEspecifico: " + (programaActual->getIdCineCampoEspecifico()) + "\n";
    texto += "  DescCineCampoEspecifico: " + programaActual->getDescCineCampoEspecifico() + "\n";
    texto += "  IdCineCodigoDetallado: " + (programaActual->getIdCineCodigoDetallado()) + "\n";
    texto += "  DescCineCodigoDetallado: " + programaActual->getDescCineCodigoDetallado() + "\n";
    texto += "  CodigoDepartamentoPrograma: " + programaActual->getCodigoDelDepartamentoPrograma() + "\n";
    texto += "  DepartamentoOfertaPrograma: " + programaActual->getDepartamentoDeOfertaDelPrograma() + "\n";
    texto += "  CodigoMunicipio: " + programaActual->getCodigoDelMunicipioPrograma() + "\n";
    texto += "  MunicipioDeOfertaPrograma: " + programaActual->getMunicipioDeOfertaDelPrograma() + "\n";

    DatosInstitucion *datosInstiActuales = unionDatos->getInstitucion();
    texto += "\nDatos de la Institución:\n";
    texto += "  CodigoInstitucion: " + datosInstiActuales->getCodigoDeLaInstitucion() + "\n";
    texto += "  IesPadre: " + datosInstiActuales->getIesPadre() + "\n";
    texto += "  InstitucionEducacionSuperiorIes: " + datosInstiActuales->getInstitucionDeEducacionSuperiorIes() + "\n";
    texto += "  PrincipalOSeccional: " + datosInstiActuales->getPrincipalOSeccional() + "\n";
    texto += "  IdSectorIes: " + (datosInstiActuales->getIdSectorIes()) + "\n";
    texto += "  SectorIes: " + datosInstiActuales->getSectorIes() + "\n";
    texto += "  IdCaracter: " + (datosInstiActuales->getIdCaracter()) + "\n";
    texto += "  CaracterIes: " + datosInstiActuales->getCaracterIes() + "\n";
    texto += "  CodigoDepartamentoIes: " + datosInstiActuales->getCodigoDelDepartamentoIes() + "\n";
    texto += "  DepartamentoDomicilioIes: " + datosInstiActuales->getDepartamentoDeDomicilioDeLaIes() + "\n";
    texto += "  CodigoMunicipioIes: " + datosInstiActuales->getCodigoDelMunicipioIes() + "\n";
    texto += "  MunicipioDomicilioIes: " + datosInstiActuales->getMunicipioDeDomicilioDeLaIes() + "\n";

    vector<Consolidado *> consolidadosActuales = unionDatos->getConsolidado();
    texto += "\nConsolidados:\n";
    for (int i = 0; i < consolidadosActuales.size(); i++)
    {
        texto += "  Sexo: " + consolidadosActuales[i]->getSexo() + " (Id: " + (consolidadosActuales[i]->getIdSexo()) + ")\n";
        texto += "  Año: " + (consolidadosActuales[i]->getAno()) + "\n";
        texto += "  Semestre: " + (consolidadosActuales[i]->getSemestre()) + "\n";
        texto += "  Inscritos: " + (consolidadosActuales[i]->getInscritos()) + "\n";
        texto += "  Admitidos: " + (consolidadosActuales[i]->getAdmitidos()) + "\n";
        texto += "  Matriculados: " + (consolidadosActuales[i]->getMatriculados()) + "\n";
        texto += "  Matriculados Primer Semestre: " + (consolidadosActuales[i]->getMatriculadosPrimerSemestre()) + "\n";
        texto += "  Graduados: " + (consolidadosActuales[i]->getGraduados()) + "\n";
    }
}

bool GestorCsv::escrituraJson(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    json jMap;
    map<std::string, UnionDatos *>::iterator it;
    for (it = unificacion.begin(); it != unificacion.end(); it++)
    {
        jMap[it->first] = convertirDatosJson(it->second);
    }

    std::ofstream archivo(ruta);

    if (!archivo.is_open())
    {
        confirmacion = false;
    }

    archivo << jMap.dump(4);
    archivo.close();

    return confirmacion;
}

json GestorCsv::convertirDatosJson(const UnionDatos *unionDatos)
{
    json j;
    ProgramaAcademico *programaActual = unionDatos->getPrograma();
    j["programa"] = {
        {"CoditoSnies", programaActual->getCodigoSniesDelPrograma()},
        {"ProgramaAcademico", programaActual->getProgramaAcademico()},
        {"IdNivelAcademico", programaActual->getIdNivelAcademico()},
        {"NivelAcademico", programaActual->getNivelAcademico()},
        {"IdNivelFormacion", programaActual->getIdNivelDeFormacion()},
        {"NivelFormacion", programaActual->getNivelDeFormacion()},
        {"IdMetodologia", programaActual->getIdMetodologia()},
        {"Metodologia", programaActual->getMetodologia()},
        {"IdArea", programaActual->getIdArea()},
        {"AreaConocimiento", programaActual->getAreaDeConocimiento()},
        {"IdNucleo", programaActual->getIdNucleo()},
        {"NucleoBasicoConocimineto", programaActual->getNucleoBasicoDelConocimientoNbc()},
        {"IdCineCampoAmplio", programaActual->getIdCineCampoAmplio()},
        {"DescCinecampoAmplio", programaActual->getDescCineCampoAmplio()},
        {"IdCineCampoEspecifico", programaActual->getIdCineCampoEspecifico()},
        {"DescCineCampoEspecifico", programaActual->getDescCineCampoEspecifico()},
        {"IdCineCodigoDetallado", programaActual->getIdCineCodigoDetallado()},
        {"DescCineCodigoDetalaldo", programaActual->getDescCineCodigoDetallado()},
        {"CodigoDepartamentoPrograma", programaActual->getCodigoDelDepartamentoPrograma()},
        {"DepartamentoOfertaPrograma", programaActual->getDepartamentoDeOfertaDelPrograma()},
        {"CodigoMunicipio", programaActual->getCodigoDelMunicipioPrograma()},
        {"MunicioDeOfertaPrograma", programaActual->getMunicipioDeOfertaDelPrograma()}};
    DatosInstitucion *datosInstiActuales = unionDatos->getInstitucion();
    j["datosInstitucion"] = {
        {"CodigoInstitucion", datosInstiActuales->getCodigoDeLaInstitucion()},
        {"IesPadre", datosInstiActuales->getIesPadre()},
        {"InstitucionEducacionSuperiorIes", datosInstiActuales->getInstitucionDeEducacionSuperiorIes()},
        {"PrincipalOSeccional", datosInstiActuales->getPrincipalOSeccional()},
        {"IdSectorIes", datosInstiActuales->getIdSectorIes()},
        {"SectorIes", datosInstiActuales->getSectorIes()},
        {"IdCaracter", datosInstiActuales->getIdCaracter()},
        {"CaracterIes", datosInstiActuales->getCaracterIes()},
        {"CodigoDepartamentoIes", datosInstiActuales->getCodigoDelDepartamentoIes()},
        {"DepartamentoDeDomiciolioDeLaIes", datosInstiActuales->getDepartamentoDeDomicilioDeLaIes()},
        {"CodigoDelMunicipioIes", datosInstiActuales->getCodigoDelMunicipioIes()},
        {"municioDeDomicilioDeLaIes", datosInstiActuales->getMunicipioDeDomicilioDeLaIes()}};
    vector<Consolidado *> consolidadosActuales = unionDatos->getConsolidado();
    j["consolidados"] = json::array();
    for (int i = 0; i < consolidadosActuales.size(); i++)
    {
        j["consolidados"].push_back({{"IdSexo", consolidadosActuales[i]->getIdSexo()},
                                     {"Sexo", consolidadosActuales[i]->getSexo()},
                                     {"Anio", consolidadosActuales[i]->getAno()},
                                     {"Semetre", consolidadosActuales[i]->getSemestre()},
                                     {"Inscritos", consolidadosActuales[i]->getInscritos()},
                                     {"Admitidos", consolidadosActuales[i]->getAdmitidos()},
                                     {"Matriculados", consolidadosActuales[i]->getMatriculados()},
                                     {"MatriculadosPrimerSemestre", consolidadosActuales[i]->getMatriculadosPrimerSemestre()},
                                     {"Graduados", consolidadosActuales[i]->getGraduados()}});
    }

    return j;
}