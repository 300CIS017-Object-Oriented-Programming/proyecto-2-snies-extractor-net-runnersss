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



bool GestorCsv::escrituraCsv(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    std::ofstream archivoSalida(ruta);
    
    if (!archivoSalida.is_open())
    {
        throw std::ios_base::failure("No se pudo abrir el archivo de salida");
    }

    // Utiliza UTF-8 BOM para permitir caracteres especiales
    archivoSalida << "\xEF\xBB\xBF";

    // Crear encabezado del CSV
    archivoSalida << "CodigoSnies;ProgramaAcademico;IdNivelAcademico;NivelAcademico;IdNivelFormacion;NivelFormacion;"
                     "IdMetodologia;Metodologia;IdArea;AreaConocimiento;IdNucleo;NucleoBasicoConocimiento;"
                     "IdCineCampoAmplio;DescCineCampoAmplio;IdCineCampoEspecifico;DescCineCampoEspecifico;"
                     "IdCineCodigoDetallado;DescCineCodigoDetallado;CodigoDepartamentoPrograma;"
                     "DepartamentoOfertaPrograma;CodigoMunicipio;MunicipioDeOfertaPrograma;CodigoInstitucion;"
                     "IesPadre;InstitucionEducacionSuperiorIes;PrincipalOSeccional;IdSectorIes;SectorIes;"
                     "IdCaracter;CaracterIes;CodigoDepartamentoIes;DepartamentoDomicilioIes;CodigoMunicipioIes;"
                     "MunicipioDomicilioIes\n";

    // Iterar sobre los datos y escribir cada línea
    for (auto it = unificacion.begin(); it != unificacion.end(); ++it)
    {
        std::string texto = escribirDatosCsv(it->second);
        archivoSalida << texto;
    }
    
    archivoSalida.close();
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
    texto += "\n";
    texto += "IdSexo;Sexo;Anio;Semestre;Inscritos;Admitidos;Matriculados;MatriculadosPrimerSemestre;Graduados\n";
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
        texto += (consolidadosActuales[i]->getGraduados())+"\n"; // Fin de la fila
    }

    return texto;
}
