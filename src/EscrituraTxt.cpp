#include "EscrituraTxt.h"

bool EscrituraTxt::escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    std::ofstream archivoSalida(ruta);
    string delimitador = Settings::DELIMITADOR;
    if (!archivoSalida.is_open())
    {
        throw std::ios_base::failure("No se pudo abrir el archivo de salida");
    }

    // Utiliza UTF-8 BOM para permitir caracteres especiales
    archivoSalida << "\xEF\xBB\xBF";

    // Crear encabezado del CSV
    archivoSalida << "CodigoSnies" << delimitador << "ProgramaAcademico" << delimitador
                  << "IdNivelAcademico" << delimitador << "NivelAcademico" << delimitador
                  << "IdNivelFormacion" << delimitador << "NivelFormacion" << delimitador
                  << "IdMetodologia" << delimitador << "Metodologia" << delimitador
                  << "IdArea" << delimitador << "AreaConocimiento" << delimitador
                  << "IdNucleo" << delimitador << "NucleoBasicoConocimiento" << delimitador
                  << "IdCineCampoAmplio" << delimitador << "DescCineCampoAmplio" << delimitador
                  << "IdCineCampoEspecifico" << delimitador << "DescCineCampoEspecifico" << delimitador
                  << "IdCineCodigoDetallado" << delimitador << "DescCineCodigoDetallado" << delimitador
                  << "CodigoDepartamentoPrograma" << delimitador << "DepartamentoOfertaPrograma" << delimitador
                  << "CodigoMunicipio" << delimitador << "MunicipioDeOfertaPrograma" << delimitador
                  << "CodigoInstitucion" << delimitador << "IesPadre" << delimitador
                  << "InstitucionEducacionSuperiorIes" << delimitador << "PrincipalOSeccional" << delimitador
                  << "IdSectorIes" << delimitador << "SectorIes" << delimitador
                  << "IdCaracter" << delimitador << "CaracterIes" << delimitador
                  << "CodigoDepartamentoIes" << delimitador << "DepartamentoDomicilioIes" << delimitador
                  << "CodigoMunicipioIes" << delimitador << "MunicipioDomicilioIes" << "\n";

    // Iterar sobre los datos y escribir cada línea
    for (auto it = unificacion.begin(); it != unificacion.end(); ++it)
    {
        std::string texto = convertirDatos(it->second);
        archivoSalida << texto;
    }

    archivoSalida.close();
    return confirmacion;
}

std::string EscrituraTxt::convertirDatos(const UnionDatos *unionDatos)
{
    std::string texto;
    string delimitador = Settings::DELIMITADOR;
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
        texto += (consolidadosActuales[i]->getGraduados()) + "\n"; // Fin de la fila
    }

    return texto;
}

bool EscrituraTxt::escrituraNoMatriculados(const std::map<std::string, std::string> &programasSinMatriculados)
{
    string delimitador = Settings::DELIMITADOR;
    map<std::string, std::string>::const_iterator itMap;
    std::ofstream archivoSalida(Settings::OUTPUT_PATH+"ProgramasSinMatriculados"+".txt");
    bool escritura = true;
    archivoSalida << "\xEF\xBB\xBF";
    archivoSalida << "CodigoSnies" << delimitador << "Programa";
    for (itMap = programasSinMatriculados.begin(); itMap != programasSinMatriculados.end(); itMap++)
    {
        archivoSalida << itMap->first << delimitador << itMap->second << std::endl;
    }
    if (!archivoSalida.is_open())
    {
        escritura = false;
    }

    archivoSalida.close();
    return escritura;
}

bool EscrituraTxt::escrituraPorcentajeDesencenso(const std::map<std::string, pair<int, int>> &programaYDifirencialAnual)
{
    bool escritura = true;
    std::map<std::string, pair<int, int>>::const_iterator itMap;
    string delimitador = Settings::DELIMITADOR;
    std::ofstream archivoSalida(Settings::OUTPUT_PATH+"ProgramasDiferenciaAnual"+".txt");
    archivoSalida << "\xEF\xBB\xBF";
    archivoSalida << "Programa" << delimitador << "2021 a 2022" << delimitador << "2022 a 2023\n";

    for (itMap = programaYDifirencialAnual.begin(); itMap != programaYDifirencialAnual.end(); itMap++)
    {
        archivoSalida << itMap->first << delimitador << itMap->second.first << delimitador << itMap->second.second << std::endl;
    }
    if (!archivoSalida.is_open())
    {
        escritura = false;
    }

    archivoSalida.close();
    return escritura;
}