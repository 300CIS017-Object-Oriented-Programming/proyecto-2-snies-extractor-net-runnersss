#include "EscrituraTxt.h"

bool EscrituraTxt::escrituraDatos(map<std::string, UnionDatos *> unificacion, string &ruta)
{
    bool confirmacion = true;
    string texto;
    map<std::string, UnionDatos *>::iterator it;
    for (it = unificacion.begin(); it != unificacion.end(); it++)
    {
        texto += convertirDatos(it->second);
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

string EscrituraTxt::convertirDatos(const UnionDatos *unionDatos)
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

    return texto;
}