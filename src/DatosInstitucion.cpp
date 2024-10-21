#include "DatosInstitucion.h"

int DatosInstitucion::getCodigoInstitucion() const
{
    return codigoInstitucion;
}

int DatosInstitucion::getIesPadre() const
{
    return iesPadre;
}

bool DatosInstitucion::getEsPrincipal() const
{
    return esPrincipal;
}

int DatosInstitucion::getIdSectorIes() const
{
    return idSectorIes;
}

std::string DatosInstitucion::getSectorIes() const
{
    return sectorIes;
}

int DatosInstitucion::getIdCaracter() const
{
    return idCaracter;
}

std::string DatosInstitucion::getCaracterIes() const
{
    return caracterIes;
}

int DatosInstitucion::getCodigoDepartamentoIes() const
{
    return codigoDepartamentoIes;
}

std::string DatosInstitucion::getDepartamentoIes() const
{
    return departamentoIes;
}

int DatosInstitucion::getCodigoMunicipioIes() const
{
    return codigoMunicipioIes;
}

std::string DatosInstitucion::getMunicipioIes() const
{
    return municipioIes;
}