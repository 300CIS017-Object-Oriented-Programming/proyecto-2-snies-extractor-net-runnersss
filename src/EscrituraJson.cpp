#include "EscrituraJson.h"

bool EscrituraJson::escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    json jMap;
    map<std::string, UnionDatos *>::iterator it;
    for (it = unificacion.begin(); it != unificacion.end(); it++)
    {
        jMap[it->first] = convertirDatos(it->second);
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

json EscrituraJson::convertirDatos(const UnionDatos *unionDatos)
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

bool EscrituraJson::escrituraNoMatriculados(map<std::string, std::string> &programasSinMatriculados)
{
    json j;
    bool escritura = true;

    map<std::string, std::string>::iterator it;
    for (it = programasSinMatriculados.begin(); it != programasSinMatriculados.end(); it++)
    {
        j[it->first] = it->second;
    }

    std::ofstream archivo(Settings::OUTPUT_PATH);
    if (!archivo.is_open())
    {
        escritura = false;
    }

    archivo << j.dump(4);
    archivo.close();
    return escritura;
}

bool EscrituraJson::escrituraPorcentajeDesencenso(std::map<std::string, std::pair<int, int>> &programaYDifirencialAnual)
{
    json j;
    bool escritura = true;
    map<std::string, pair<int, int>>::iterator itMap;
    for (itMap = programaYDifirencialAnual.begin(); itMap != programaYDifirencialAnual.end(); itMap++)
    {
        j[itMap->first] = {
            {"2021 a 2022", itMap->second.first},
            {"2022 a 2023", itMap->second.second},
        };
    }

    std::ofstream archivo(Settings::OUTPUT_PATH);
    if (!archivo.is_open())
    {
        escritura = false;
    }

    archivo << j.dump(4);
    archivo.close();
    return escritura;
}
